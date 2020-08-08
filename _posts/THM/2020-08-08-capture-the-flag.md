---
layout: post
permalink: /posts/thm/capture-the-flag
title: "THM write-up: CaptureTheFlag"
date: 2020-08-08 12:37
tags: tryhackme CTF recon stego reverse_engineer crypto 
description: "This time I'm going to do a write-up on Boiler CTF. This is an intermediate CTF challenge. This room is written by MrSeth6797."
---

![titlecard](/assets/images/THM/2020-08-08-capture-the-flag/1.png)

[Link: https://tryhackme.com/room/functf](https://tryhackme.com/room/functf)

CTF or Capture the Flag is a special kind of information security competition.  There are three common types of CTFs: Jeopardy, Attack-Defence and mixed (by [ctftime](https://ctftime.org/ctf-wtf/)). The challenge involves the knowledge of cryptography, steganography, reverse engineering and web hack. What can you gain from CTF challenge? The purpose of the CTF challenge is to improve skills such as digital forensics and penetration testing. Most importantly, it is fun and satisfies.

This challenge is created by [falconfeast](https://tryhackme.com/p/falconfeast). Trust me, this CTF challenge is really fun. Without further ado, let's dive in.

## Task 1: Text inside image

### Part 1: Flag

This task is the easiest challenge, open the image as .txt file and scroll to the bottom of the page. 

![text flag](/assets/images/THM/2020-08-08-capture-the-flag/2.png)

### Part 2: Flag

For this part, you need to find the metadata or EXIF of the image file. I used the [binary viewer](https://www.proxoft.com/BinaryViewer.aspx)  to analyze the image file and came across with the following encoded flag.

![image flag](/assets/images/THM/2020-08-08-capture-the-flag/3.png)

This is a [base64](https://www.base64decode.org/) encoded string (dHJ5aGFja21lezRsd2F5NV9jaDNja19tM3Q0ZGE3NH0K). Decoding the string to reveal the flag.

![base64](/assets/images/THM/2020-08-08-capture-the-flag/4.png)

## Task 2: Binwalk

As suggested by the title "walk the bin out", a simple google will reveal a tool called [Binwalk](https://github.com/ReFirmLabs/binwalk). This tool analyzes and extracting information/file from an image. Analyze the image with the following command:

```
binwalk -B walk.png
```

Look like we have a gzip file and TIFF image files inside the image.

![binwalk](/assets/images/THM/2020-08-08-capture-the-flag/5.png)

Then, we can extract the files using the following command:

```
binwalk -e walk.png
```

After the extraction, open up the "29A72" file as .txt and reveal the encoded flag (T1JaSFMyREJNTlZXMlpMM01JWVc0NVpVTlJWVjZNRFNMNVREQTRSVE5WWFRLNUQ1Qkk9PT09PT0K).

![file](/assets/images/THM/2020-08-08-capture-the-flag/6.png)

![extracted file](/assets/images/THM/2020-08-08-capture-the-flag/7.png)

The flag is encoded twice with 2 different bases. You have to decode the flag with [base64](https://www.base64decode.org/) and then [base32](https://emn178.github.io/online-tools/base32_decode.html) and reveal the following flag:

![base flag](/assets/images/THM/2020-08-08-capture-the-flag/8.png)

## Task 3: Steghide

The answer for the tool is on the title. However, the title is encoded with [base85/ACSII 85](https://www.dcode.fr/ascii-85-encoding). Decoding the string reveals the tool called [steghide](http://steghide.sourceforge.net/). Steghide is another stenography tool to hide various data inside an image. The data can be extracted by entering the following command:

```
steghide extract -sf hide.jpg 
```

However, you are prompted to enter the passphrase and where the hell is the passphrase?

![steghide](/assets/images/THM/2020-08-08-capture-the-flag/9.png)

Refer to the Task 1, part 2. The passphrase is hidden as EXIF. 

![steg pass](/assets/images/THM/2020-08-08-capture-the-flag/10.png)

This passphrase is encoded with [base32](https://emn178.github.io/online-tools/base32_decode.html) (The room's author sure love bases). Decoding it yield 'tryh4ckm3'. Enter the passphrase and get the flag in .txt file.

![steg flag](/assets/images/THM/2020-08-08-capture-the-flag/11.png)

## Task 4: zsteg

The tool's name is somehow ciphered using ROT cipher and we are not sure which ROT is used. The only thing we can do is brute force it using [ROT cipher](https://www.dcode.fr/rot-cipher).

![Rot](/assets/images/THM/2020-08-08-capture-the-flag/12.png)

The cipher reveals a tool called zsteg. Another hint (the 'lsb' or least significant bit) is given and we can launch our zsteg with the following command:

![zsteg flag](/assets/images/THM/2020-08-08-capture-the-flag/13.png)

We get another encoded flag (credit to the author, 4wbWyHV1VA43QJtvWdw8pLCwkADDQ7ZdYkz39KsKaXUeLtPy9DShWSp). The flag looks like a base64 but actually, it is not. The flag is encoded as [base58](https://www.browserling.com/tools/base58-decode). However, it is not the end, the flag is encoded twice with different bases. After base58, you still need to decode it with [base32](https://emn178.github.io/online-tools/base32_decode.html) and reveal to the following flag.

![zsteg true flag](/assets/images/THM/2020-08-08-capture-the-flag/14.png)

## Task 5: Broken PNG?

There is a big hint given in this task, the "HEADER".  The [first eight](http://www.libpng.org/pub/png/spec/1.2/PNG-Structure.html) byte of PNG file should be :

```
89 50 4e 47 0d 0a 1a 0a
```

Referring to the corrupted PNG, the first eight bytes look like this

![fix it](/assets/images/THM/2020-08-08-capture-the-flag/15.png)

Changing the first 4 bytes into "89 50 4e 47" to reveal the flag.

![fixed](/assets/images/THM/2020-08-08-capture-the-flag/16.png)

## Task 6: Flag spectrum

The flag is somehow hidden in the .wav file and the only hint given is "the spectrum". This task can be solved by any tool and for this case, I going to use [wavepad](https://www.nch.com.au/wavepad/index.html) to analyze the wave file. First and foremost, locate tools>TFFT and reveal the flag.

![wavepad](/assets/images/THM/2020-08-08-capture-the-flag/17.png)

## Task 7: Ciphers

You can finish this task by using the brute force [ROT cipher](https://www.dcode.fr/rot-cipher) (except part 4) method and then choose the right technique to decipher the text.

### Part 1

Technique: Ceaser chipher

### Part 2

Technique: ROT 13

### Part 3

Technique: ROT 47

### Part 4

Technique: Vigenere cipher

You cannot use ROT cipher for this part as the text is ciphered as vigenere cipher. You have to refer to the [table](https://pages.mtu.edu/~shene/NSF-4/Tutorial/VIG/Vig-Base.html) to complete the task. The first 9 characters of the cipher text is known, given that "rbcfkgiwi" = "tryhackme". The key can be obtained using the known cipher and the key is yke. With both key and the cipher text, we can get the flag.

## Task 8: Pigpen cipher

Don't worry, this is not an alien text! This is the [pigpen cipher](https://www.dcode.fr/pigpen-cipher) using tic-tac-toe and cross X. Simply input the image characters and reveal the flag.

## Task 9: DNA cryptography

This task is little bit tricky. At first glance, I'm used the real [DNA codon table](https://en.wikipedia.org/wiki/DNA_codon_table) to solve the challenge but ended with failure. This is because the real DNA codon table missed some alphabet and all the numbering. Thanks to the GitHub user, [John](https://github.com/JohnHammond/ctf-katana) who gave me an idea to solve the challenge. The answer is shown on the table below:

![DNA](/assets/images/THM/2020-08-08-capture-the-flag/18.png)

As you can see, each 3 letters of the cipher text represent 1 English letter/number. You can either do it by easy way (coding) or hard way (trace it one-by-one). For me, i created a python script for the challenge.

```python
#!/usr/bin/env python

import sys

mappings = {
	'AAA' : 'a',
	'AAC' : 'b',
	'AAG' : 'c',
	'AAT' : 'd', 
	'ACA' : 'e',
	'ACC' : 'f',
	'ACG' : 'g',
	'ACT' : 'h',
	'AGA' : 'i',
	'AGC' : 'j',
	'AGG' : 'k',
	'AGT' : 'l',
	'ATA' : 'm',
	'ATC' : 'n',
	'ATG' : 'o',
	'ATT' : 'p',
	'CAA' : 'q',
	'CAC' : 'r',
	'CAG' : 's',
	'CAT' : 't',
	'CCA' : 'u',
	'CCC' : 'v',
	'CCG' : 'w',
	'CCT' : 'x',
	'CGA' : 'y',
	'CGC' : 'z',
	'CGG' : 'A',
	'CGT' : 'B',
	'CTA' : 'C',
	'CTC' : 'D',
	'CTG' : 'E',
	'CTT' : 'F',
	'GAA' : 'G',
	'GAC' : 'H',
	'GAG' : 'I',
	'GAT' : 'J',
	'GCA' : 'K',
	'GCC' : 'L',
	'GCG' : 'M',
	'GCT' : 'N',
	'GGA' : 'O',
	'GGC' : 'P',
	'GGG' : 'Q',
	'GGT' : 'R',
	'GTA' : 'S',
	'GTC' : 'T',
	'GTG' : 'U',
	'GTT' : 'V',
	'TAA' : 'W',
	'TAC' : 'X',
	'TAG' : 'Y',
	'TAT' : 'Z',
	'TCA' : '1',
	'TCC' : '2',
	'TCG' : '3',
	'TCT' : '4',
	'TGA' : '5',
	'TGC' : '6',
	'TGG' : '7',
	'TGT' : '8',
	'TTA' : '9',
	'TTC' : '0',
	'TTG' : ' ',
	'TTT' : '.'
	}

#open file
f = open(sys.argv[1]).read().strip()

#flag array
flag = []

#Mapping
for x in range(0,len(f),3):
	piece = f[x:x+3]
	flag.append(mappings[piece])
	
print (''.join(flag))
```

## Task 10: Exclusive or

Exclusive or (XOR) is a well known bit-wise operation in programming. It was originate from semiconductor called XOR gate.

![xor](/assets/images/THM/2020-08-08-capture-the-flag/19.png)

[Xortool](https://github.com/hellman/xortool) is used to solve the challenge. The objective of this challenge is to decrypt the XOR cipher in brute force way. Save the hex code as .hex and punch in the following command:

```
xortool -x -b XOR.hex
```

![xortool](/assets/images/THM/2020-08-08-capture-the-flag/20.png)

Do not let the output fool you. The actual key length is not 5 because you can't find 100% valid char in the report. The second possibility is the key length with 1. Punch in the following command: 

```
xortool -x -b XOR.hex -l 1
```

Then, visit the file called "filename-char_used-perc_valid.csv". There are 4 files showing 100% valid characters. 

![xortool output](/assets/images/THM/2020-08-08-capture-the-flag/21.png)

![xortool flag](/assets/images/THM/2020-08-08-capture-the-flag/22.png)

## Task 11: Morse code

This task is easy, you just needed to replace the following:

- dat --> .
- di --> -
- t -->  /

The final outcome should be like this:

```
. … -.-- / .-- / .-.. … --. . ---- / - / .-.. -. -.- / - / --. --- / -- / .- / ..- / -. .- / .-.. . ---- / -- / .- / ..- / . … - / .- / .-.- / -.- / .-.. -..- / . . ---- / - / --- / - / .-- / -. .-.. --- / -.-.-. --.- / -.-- / -. ..- / -- / --- / -- / .- / . ---.. -.- / .- / ----. . -- / ….. .- / ----. -.-- / .. ….. -.- / --- / ---.. .-.- / ….. .-- / ---..
```

Putting to code into the Morse code [translator](https://www.dcode.fr/morse-code) and the flag will be revealed.

## Task 12: Reverse engineer (Part 1)

The challenge can be solved in two ways: 

- Open the file as .txt and find the flag (easy way).
- Open the file using IDA pro (original way).

I would like to solve this challenge using the IDA pro because the tool will be handy in the next challenge. Boot up the IDA pro and open the flag file. After that, go to view --> open subviews --> strings until you come across with two encrypted messages.

![IDA string](/assets/images/THM/2020-08-08-capture-the-flag/23.png)

Both messages are encrypted with [Base64](https://www.base64decode.org/) and the first message is basically trolling you. The real flag is on the second red box.

## Task 13: Inverse mapping

The long string can be decrypted using [base58](https://www.browserling.com/tools/base58-decode) and you will come across with the following output. 

![base58 decode](/assets/images/THM/2020-08-08-capture-the-flag/24.png)

The output looked like a script and a hint: "reverse this". For me, I'm only interested with the mapping. The script is rewritten using python.

```python
#!/usr/bin/env python

import sys

mappings = {'a':'! ', 'b':'@ ', 'c':'/ ', 'd':'# ', 'e':'$ ', 'f':'% ', 'g':'^ ', 'h':'& ', 'i':'* ', 'j':'(', 'k':') ', 'l':'- ', 'm':'_ ', 'n':'+ ', 'o':'= ', 'p':'{ ', 'q':'} ', 'r':'[ ', 's':'] ', 't':': ', 'u':'; ', 'v':'< ', 'w':'> ', 'y':'? ', 'x':'" ', 'z':'| ', '{':'-?', '}':'?-', '1': "!@", "2":"@#", "3":"#$", "4":"$%", "5": "%^", "6":"^&", "7":'&*', "8":"*(", "9":")_","0":"[]", ' ': "<>", "_":"~ "}

#inverse mappings
if(sys.version_info[0] < 3):
	inv_mappings = {v:k for k, v in mappings.iteritems()}
else:
	inv_mappings = {v:k for k, v in mappings.items()}

#open file
f = open(sys.argv[1]).read().strip()

#flag array
flag = []

#Mapping
for x in range(0,len(f),2):
	piece = f[x:x+2]
	flag.append(inv_mappings[piece])
	print(''.join(flag))
	
print (''.join(flag))
```

Also, I have to rearrange the cipher text into:

```
@ = = <>[ $ < $ [ ] * + ^ <>> * : & = ; : <>@ * + ! [ ? <>@ = = <>] & = > <>; ] <>] = _ $ <>] : ! / ) <>@ = ? <>= & <>! + # <>^ * < $ <>_ $ <>_ ? <># ! _ + <>% - ! ^ <>: [ ? & ! / ) _ $ -?> #$[ !@# ~ ] ? _ @ []- %^?-
```

Because I'm reusing the code from the DNA cryptography by assuming two characters is equivalent to 1 English word or number. 

## Task 14: Reverse engineer (Part 2)

This task is quite challenging and requires basic knowledge on reverse engineering. You can visit this [video](https://www.youtube.com/watch?v=cATBah30jk0) tutorial. The explanation is simple and clear. Now, time to boot up our IDA pro again!

Using the method from the previous task (searching for the string), you will come across with this: 

![strings](/assets/images/THM/2020-08-08-capture-the-flag/25.png)

You think the flag just sitting there for you to pick up? NO, that is not the flag we looking for and it was deep inside it. Now, visit jump --> jump to entry point and we have the following function:

![flag](/assets/images/THM/2020-08-08-capture-the-flag/26.png)

As you can see, we found a suspicious function called 'flag' and you can check it out. From now on, i will gone through block by block and all comments is written inside the block.

### Block 1: Initialization block

![init block](/assets/images/THM/2020-08-08-capture-the-flag/27.png)

The first block storing the 21 bytes encrypted flag into the stack and initialize the counter value.

### Block 2: Compare string length

![compare block](/assets/images/THM/2020-08-08-capture-the-flag/28.png)

The second block is comparing the string length.

### Block 3: Decode the flag 

![decode block](/assets/images/THM/2020-08-08-capture-the-flag/29.png)

From the figure above, the flag can be decoded using XOR of 0x10. The decoded flag can be written as: 

```
52 33 76 33 72 33 64 5F 74 68 31 73 5F 6C 31 6B 33 5F 67 30 64
```

Convert the flag into ASCII and reveal the flag.

## Task 15: Trivial question

### Part 1: Who stop the worst ransomware? 

The ransomware here is referred as wanna-cry and the person who stop it is known as [Marcus Hutchins a.k.a MalwareTech](https://en.wikipedia.org/wiki/Marcus_Hutchins).

### Part 2: Who used by all devices to send error messages?

The answer is ICMP (Internet Control Message Protocol) and the hint is provided by non other than The Author!!!

### Part 3: Which CTF team is open for all?

The CTF team is known as [OpenToAll](https://opentoallctf.github.io/), visit them now.

## Task 16: Brainfuck

The downloaded text is encoded with [base64](https://www.base64decode.org/). Decode the text in result of: 

```
++++++++++[>+>+++>+++++++>++++++++++<<<<-]>>>>++++++++++++++++.--.+++++++.-----------------.-------.++.++++++++.++.--------.++++++++++++++++++++++.<+++++++++++++++++.+++++++++++++++++.<++++++++++++++++++++++++++++++++++.>>-------.<---------.<---------.+++++++++++++++++.---------------------.>.<+++++++++++++++++++++.---------------------.>-------------------..+++++++++++++++++++.++++++++++.<++.>----------.>.<+++++++++.+.>-.++++++++++.
```

What the freak is this? This is a program called brainfuck and it only consists of 8 characters and hard to learn with. One can run this code by copying the text into [brainfuck compiler](https://tio.run/#brainfuck).

## Task 17: Web

This challenge required the user connected to tryhackme [openVPN](https://tryhackme.com/access) service. After that, launch your browser and copy given IP address into the URL. The task consists of 2 parts.

### Part 1: URL (IP:17000)

After punched in the URL, you will be direct to this page:

![webpage](/assets/images/THM/2020-08-08-capture-the-flag/30.png)

Clicking the button will redirect you to the flag. However, you will received an 404 error page.

![404](/assets/images/THM/2020-08-08-capture-the-flag/31.png)

The URL should be /g#me_me_the_d#mn_fl#g but the error showing /g instead. From URL point of view, # is used as  [fragment_identifier](https://en.wikipedia.org/wiki/Fragment_identifier) or an id to direct the user to specific section without scrolling through the page which make the character after # an id instead of an element of URL directory. Now, we have identified the problem and how we represent the # as part of the URL directory instead of id? URL encoder might come in handy for this scenario. The encoded # can be represented by %23. Input the following URL to reveal the flag

```
http://<machine IP>:17000/g%23ve_me_the_d%23mn_fl%23g
```

### Part 2: PHP (IP:17001)

You will be redirect to the following page:

![webpage php](/assets/images/THM/2020-08-08-capture-the-flag/32.png)

Clicking the link will simply redirect you to php script and that is the hint. Your objective is to get the flag() function. There are two conditions to get the flag

- PHP GET name must be "golden_word"
- PHP GET value must be "nevergiveup"

Simply putting the url "IP:17001/?golden_word=nevergiveup" will not work because there are one function called "preg_replace" which replace the string 'nevergiveup' into an empty string  (second condition cannot fulfilled). Changing 'nevergiveup' to hex only work for operand "==" but not for "===". The only way is changing 'nevergiveup' into '**n**nevergiveup**e**nevergiveup**v**nevergiveup**e**nevergiveup**r**nevergiveup**g**nevergiveup**i**nevergiveup**v**nevergiveup**e**nevergiveup**u**nevergiveup**p**'.

Did you see it? All the non-bold text will be removed by the function and the bold text will join up as 'nevergiveup'. The input URL should be:

```
http://<machine IP>:17001/index.php?golden_word=nnevergiveupenevergiveupvnevergiveupenevergiveuprnevergiveupgnevergiveupinevergiveupvnevergiveupenevergiveupunevergiveupp
```

Finally, the flag is revealed.

![php flag](/assets/images/THM/2020-08-08-capture-the-flag/33.png)

## Task 18: Ook!

Almost similar to brainfuck, this is another esolang called Ook (or oak). Decode the text using [base64](https://www.base64decode.org/) and get the following text :

```
....................!?.?...?.......?...............?....................?.?.?.?.!!?!.?.?.?.?................................!.!!!!!...............!.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!.!!!!!!!!!!!!!!!.....!.................!.....!.!!!!!!!!!!!!!!!!!.............................................!.?.?.....................................!.!..?.?!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!.!!!!!!!!!!!!!!!!!!!!!!!!!.....................!.?.?...........!..?.?!!!!!!!!!!!!!!!!!!!!!.....!.!!!!!...........................!.!!!!!!!!!!!!!!!!!!!!!!!...........................!.!!!!!!!!!!!!!!!.............................!.?.?.!!!..?.?!!!!!!!!!!!!!!!!!!!!!!!!!!!!!.!!!!!.?.!!!!!!!!!!!!!!!..?................................................!.
```

Run this code in any [compiler](https://www.dcode.fr/ook-language) and the flag will be revealed.

## Conclusion

This is the end of the challenge and hope you can learn something new from this CTF walkthrough. To be honest, it took me almost 5 days to finish up this challenge (of course, with guidance from falconfeast, the creator of the room). However, I'm really enjoy it and feeling satisfy on the completion. Until next time :)