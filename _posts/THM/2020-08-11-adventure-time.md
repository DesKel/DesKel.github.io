---
layout: post
permalink: /posts/thm/adventure-time
title: "THM write-up: Adventure Time"
date: 2020-08-11 17:46
tags: tryhackme CTF recon privilege_escalate
description: "Another day, another write-up on tryhackme challenge. I would prefer this walkthrough as a how-to basic on pentesting."
---

![titlecard](/assets/images/THM/2020-08-11-adventure-time/1.png)

[Link: https://tryhackme.com/room/adventuretime](https://tryhackme.com/room/adventuretime)

Greeting again, welcome back to another tryhackme CTF walkthrough. Today, we are going through the toughest puzzle-based CTF in tryhackme server. It took me around 2 and a half days to finish this challenge with major guidance from the creator, n0w4n. This write-up is specially written for people who lost inside the maze. I'm sure you will learn a lot from this room as it is rich in text encryption and cipher. Without further ado, let's start the walkthrough.

## Task 1: Capture the flag

There are 5 flags inside the machine. Gonna capture them all!

### Task 1-0: Getting inside the machine

Your first task is to gain access to the machine. How you gonna do that?

#### 1) Nmap

First and foremost, let's fire up our Nmap scanner with the following command

```
nmap -Pn -p- -A -v <Machine IP>
```

![nmap](/assets/images/THM/2020-08-11-adventure-time/2.png)

![nmap more](/assets/images/THM/2020-08-11-adventure-time/3.png)

![nmap more more](/assets/images/THM/2020-08-11-adventure-time/4.png)

There are 6 open ports available on the machine which is Port 21 (FTP), Port 22 (SSH), Port 80, Port 443 (Port) and Port 31337 (Unknown). Let check each of the port.

#### 2) Port 21 (FTP)

![ftp](/assets/images/THM/2020-08-11-adventure-time/5.png)

There is a total 6 picture in the FTP server. Download each of them and check with the EXIF tool.

![exif](/assets/images/THM/2020-08-11-adventure-time/6.png)

Combine all of them and you will something interesting. lol. We will skip port 22 since we are not sure about the login user and pass. Let's move on to Port 80.

#### 3) Port 80

![http](/assets/images/THM/2020-08-11-adventure-time/7.png)

Look like we get a 404 response from port 80. Next port, please.

#### 4) Port 443

![Jake](/assets/images/THM/2020-08-11-adventure-time/8.png)

Make sure you add certificate execption for the port. Now, we got a message from Finn. Nothing we can do here, let's move on the next port.

#### 5) Port 31337

If you refer to the Nmap fingerprint of the port, you will notice something unusual. It looks like a communication socket to me. Whenever I try to communicate with the port using telnet, I got the following reply.

![telnet](/assets/images/THM/2020-08-11-adventure-time/9.png)

A magic word huh? Well, we have zero clues about the magic word. Great, we are stuck now. What to do? We haven't brute force the webserver directory.

#### 6) gobuster

gobuster is the way to go. However, a wrong wordlist will be going to cost you. After consulting with n0w4n, dirbuster/directory-list-lowercase-2.3-medium.txt is a suitable wordlist used to brute-force with. So, be patient, it going to take you some time.

```
gobuster dir -u https://<machine IP> -w /usr/share/dirbuster/wordlists/directory-list-lowercase-2.3-medium.txt -k
```

![gobuster](/assets/images/THM/2020-08-11-adventure-time/10.png)

After 10 to 20 mins, we are able to locate the hidden directory. /candybar/.

#### 7) The candybar

![more http](/assets/images/THM/2020-08-11-adventure-time/11.png)

A base32 text. We are going to decode this one. (Tips: just copy the text from the source code).

![base 32](/assets/images/THM/2020-08-11-adventure-time/12.png)

Huh, we don't understand what the sentence means. Maybe a ceaser cipher?

![ceaser cipher](/assets/images/THM/2020-08-11-adventure-time/13.png)

After decoding the ciphertext using [ceaser cipher](https://cryptii.com/pipes/caesar-cipher), we have to check with the SSL certificate.

![SSL](/assets/images/THM/2020-08-11-adventure-time/14.png)

There is a numerous way to check the SSL certificate. But the easiest way is using the browser.

![inside SSL](/assets/images/THM/2020-08-11-adventure-time/15.png)

Playing around the certificate, I stumble across two different domains. What does this mean? After consulting with the creator again, the webserver actually running with virtual hosting. Take a look at the [tutorial](https://www.digitalocean.com/community/tutorials/how-to-set-up-apache-virtual-hosts-on-ubuntu-16-04), if you are not sure about virtual hosting. In short, virtual hosting is accessing multiple domains with only a single IP address. For Linux system, you need to configure your /etc/hosts. For window host, check [this documentation](https://gist.github.com/zenorocha/18b10a14b2deb214dc4ce43a2d2e2992).

![virtual host](/assets/images/THM/2020-08-11-adventure-time/16.png)

After that, access to https://land-of-ooo (make sure you add https://).

#### 8) Land-of-ooo

![more jake](/assets/images/THM/2020-08-11-adventure-time/17.png)

Now we found jake. If seem that nothing we can do about the page. Here goes the gobuster again.

![more gobuster](/assets/images/THM/2020-08-11-adventure-time/18.png)

This time is /yellowdog/

#### 9) yellow dog

![jakes](/assets/images/THM/2020-08-11-adventure-time/19.png)

Make sure you trail a '/' at the end of the directory or else, you will be redirected to Finn page. After surveying the website, nothing out of ordinary. Let's try with gobuster again by using a recursive way.

![I love gobuster](/assets/images/THM/2020-08-11-adventure-time/20.png)

Oops, look like we have another hidden directory, /bananastock/

#### 10) Banana stock

![banana](/assets/images/THM/2020-08-11-adventure-time/21.png)

I guess the banana guard speaking morse code. Once again, copy the morse code inside the page source and dump into [morse code translater](https://www.dcode.fr/morse-code).

![morse code](/assets/images/THM/2020-08-11-adventure-time/22.png)

The unknown symbol represents space. Sorry for the lousy translator. In the end, we get **"THE BANANAS ARE THE BEST!!!"**. We going to save it for later use. Time for another gobuster (I promise, this is the last time).

Well, well,  well, another hidden directory. This time is /princess/

#### 11) Princess

![princess bubblegum](/assets/images/THM/2020-08-11-adventure-time/23.png)

Is the princess bubblegum! Look like she got a little secret inside the lappy. Checking the source code of the page, it reveals another encrypted text.

![aes info](/assets/images/THM/2020-08-11-adventure-time/24.png)

It is an AES encrypted text message. All the information provided ease our way to decrypt the message. You can try the online AES decryption tool.

![AES](/assets/images/THM/2020-08-11-adventure-time/25.png)

You still can decrypt the message without the VI. After that, we get a magic word: ricardio. Still, remember the port 31337? We can try to input this magic.

![telnet reveal](/assets/images/THM/2020-08-11-adventure-time/26.png)

We got a username. Let give it a try on the SSH shell by using this username and a phrase we obtained before (THE BANANAS ARE THE BEST!!!)

![SSH inisde](/assets/images/THM/2020-08-11-adventure-time/27.png)

Hacking success, we are not obtained the SSH shell.

### Task 1-1: Flag 1

Time for our first flag which is located at apple-guards directory

![user flag](/assets/images/THM/2020-08-11-adventure-time/28.png)

Don't even try to bother with flag.txt, it was an oopsie by the creator :). The file we are interested in here is the mail or mbox.

![mbox](/assets/images/THM/2020-08-11-adventure-time/29.png)

The file is hidden somewhere, by marceline. What is in your mind? We need to search for a file which is created by marceline. Maybe this command?

```
find / -type f -user 'marceline' -ls 2>/dev/null
```

![executable](/assets/images/THM/2020-08-11-adventure-time/30.png)

based on the color, it can tell us that file is an executable file. Run the file using ./helper (run inside the /etc/fonts directory)

![cipher](/assets/images/THM/2020-08-11-adventure-time/31.png)

Another puzzle! A ciphertext and a key? Look like a vigenere cipher to me. But where is the key? Actually the answer is in front of us, Read this sentence, The key to solve this puzzle is **gone**. Get that?

![decipher](/assets/images/THM/2020-08-11-adventure-time/32.png)

![answer](/assets/images/THM/2020-08-11-adventure-time/33.png)

That's it, we now obtain marceline's ssh password.

### Task 1-2: Flag 2

Login to marceline's ssh shell and capture the second flag.

![marceline](/assets/images/THM/2020-08-11-adventure-time/34.png)

We got a note from marceline. Let's check it out.

![note](/assets/images/THM/2020-08-11-adventure-time/35.png)

Look like a binary? Nope, that is NOT an actual binary number. Its something related to esolang or esoteric language such as brainfuck. As first glance, I thought it is a [binaryfuck](https://esolangs.org/wiki/Binaryfuck), a deviation from brainfuck. For binary fuck, the number of 111 (end loop) must be equal to 110 (open loop). After checking the frequency of the 3-bit binary, there is no way that both frequencies match.

![not binaryfuck](/assets/images/THM/2020-08-11-adventure-time/36.png)

After another consultancy from the creator, the [spoon esolang](https://esolangs.org/wiki/Spoon) is the correct way to solve this puzzle. If you are a Windows user, you can [convert the exe](https://github.com/MarquisdeGeek/spoon). However, if you are a Linux user, you can try my freshly coded Spoon --> brainfuck converter.

```python
mport sys

with open(sys.argv[1],'r') as my_file:
	data = my_file.read()

brain = ""
skip = 1
reset = 0

for i in range(len(data)):
	if (reset%skip == 0):
		if (data[i] == '1'):
			brain += '+'
			skip = 1
			reset = 0
		elif (data[i] == '0'):
			if(data[i+1] == '0'):
				if (data[i+2] == '0'):
					brain += '-'
					skip = 3
					reset = 0
				elif (data[i+2] == '1'):
					if(data[i+3] == '0'):
						if(data[i+4] == '0'):
							brain += '['
							skip = 5
							reset = 0
						elif(data[i+4] == '1'):
							if(data[i+5] == '0'):
								brain += '.'
								skip = 6
								reset = 0
							elif(data[i+5]=='1' and data[i+6]=='0'):
								brain +=','
								skip = 7
								reset = 0
					elif(data[i+3] == '1'):
						brain += ']'
						skip = 4
						reset = 0

			elif(data[i+1] == '1'):
				if (data[i+2] == '0'):
					brain += '>'
					skip = 3
					reset = 0
				elif (data[i+2] == '1'):
					brain += '<'
					skip = 3
					reset = 0

	reset +=1

print (brain)
```

Run the python code and translate the binary to the brainfuck. After that, dump into any brainfuck translator, you should see the following output.

![brainfuck](/assets/images/THM/2020-08-11-adventure-time/37.png)

Run the python code and translate the binary to the brainfuck. After that, dump into any [brainfuck](https://www.dcode.fr/brainfuck-language) translator, you should see the following output.

![translate](/assets/images/THM/2020-08-11-adventure-time/38.png)

Guess what? Another magic word!. Go back to port 31337 and enter the magic word.

![new cred](/assets/images/THM/2020-08-11-adventure-time/39.png)

It is peppermint-butler's ssh access pass.

### Task 1-3: Flag 3

Login to peppermint-butler's SSH shell and capture the flag.

![butler flag](/assets/images/THM/2020-08-11-adventure-time/40.png)

Now, we got an image file inside peppermint butler's directory. We are going to pull that file using Filezilla or SCP.

![butler](/assets/images/THM/2020-08-11-adventure-time/41.png)

I'm highly suspect something is stored inside the image file. A steghide without password does not yield another but I'm not giving up yet. After performing a file search in the name of peppermint-butler, I come across two specific file name.

```
find / -type f -user 'peppermint-butler' -ls 2>/dev/null
```

![stegtext](/assets/images/THM/2020-08-11-adventure-time/42.png)

![ziptext](/assets/images/THM/2020-08-11-adventure-time/43.png)

One is steg.txt and the other one is zip.txt.  Let's read the files.

![read stegtext](/assets/images/THM/2020-08-11-adventure-time/44.png)

The steg.txt is a passphrase for steghide. Extracting the stego image yield a compressed zip file. In case you don't know how to use steghide to extract the file.

```
steghide extract -sf butler-1.jpg
```

![protected](/assets/images/THM/2020-08-11-adventure-time/45.png)

Look like the zip file is password protected. Reading the zip.txt reveal the pass for the zip file.

![read ziptext](/assets/images/THM/2020-08-11-adventure-time/46.png)

So, what is inside the secret txt?

![secret](/assets/images/THM/2020-08-11-adventure-time/47.png)

The text file actually a secret diary. Huh, maybe that is the passphrase for gunter but somehow the last four-letter is missing. I guess we have to use the hydra to brute force gunter's ssh shell. There are two-way to solve the puzzle, the crunch way or the lazy way. I highly recommend the lazy way because it is the fastest and efficient.

If you wanted to follow my lazy way, let's take a look at the passphrase. The passphrase all contain proper English words which mean that the last should be a legit English word. Visit this [website](https://www.morewords.com/wordsbylength/5s) and copy all the 5 letters English word that starts with an 's'. Just copy, no need to made a new line and also, make sure toggle off the 'show score' before copying it. If you are done, create your own python script by adding 'The Ice King ' in front of the letter. You can refer to my code.

```python
file = open('sfile','r')
data = file.read()
file.close()

process = ""
xor = ""

for i in range(len(data)):
	if(i%5 == 0 and i != 0):
		process += 'The Ice King ' + data[i:i+5]
		process += "\n"

file = open('spass','w')
file.write(process)
file.close()
```

If you are done, your wordlist should look like this.

![wordlist](/assets/images/THM/2020-08-11-adventure-time/48.png)

Launch your hydra by using the following command

```
hydra -l gunter -P spass ssh://<Machine IP>
```

![hydra](/assets/images/THM/2020-08-11-adventure-time/49.png)

After a minute, gunter's ssh password should reveal in front of you.

### Task 1-4: Flag 4

Login to gunter's ssh shell and capture flag 4.

![guntar shell](/assets/images/THM/2020-08-11-adventure-time/50.png)

The final flag will be a little bit tricky. No more puzzle now, this is real-life exploitation. Let's check the suid file using the following command.

```
find / -perm /4000 2>/dev/null
```

![exim](/assets/images/THM/2020-08-11-adventure-time/51.png)

The Exim program caught my attention. What is the version?

![exim version](/assets/images/THM/2020-08-11-adventure-time/52.png)

Version 4.9. After a short searching based on the version, I come across this [local privilege escalation exploit](https://www.exploit-db.com/exploits/46996). Before we are going to copy the script and run the exploit, we need to make sure two things. The first thing is the GCC (Thank user n0w4n, the creator).

![first condition](/assets/images/THM/2020-08-11-adventure-time/53.png)

First condition, check. The second condition is the port run by Exim. First off, check the configuration file in /etc/exim.

![second condition](/assets/images/THM/2020-08-11-adventure-time/54.png)

The Exim is operated in port 6000. The second condition, checked. Copy the script into the temp folder, change the port number, change the permission to 777 and run the script.

![script](/assets/images/THM/2020-08-11-adventure-time/55.png)

![exploit complete](/assets/images/THM/2020-08-11-adventure-time/56.png)

Congratulation, you are now rooted in the machine. Time for the final flag.

### 5) Task 1-5: Flag 5

The flag is located inside princess bubblegum's directory

## Conclusion

That's all for the ultimate long puzzle walkthrough. It is a fun challenge, to be honest. Until next time ;)
