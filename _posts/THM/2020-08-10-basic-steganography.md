---
layout: post
permalink: /posts/thm/basic-steganography
title: "THM write-up: Basic Steganography"
date: 2020-08-10 19:53
tags: tryhackme CTF steganography
description: "Another day, another tryhackme room challenge. Today, we are going for a simple steganography challenge."
---

![titlecard](/assets/images/THM/2020-08-10-basic-steganography/1.png)

[Link: https://tryhackme.com/room/basicsteganographyal](https://tryhackme.com/room/basicsteganographyal)

Another day, another tryhackme room challenge. Today, we are going for a simple steganography challenge. If you are really in love with stego challenge, you can try [rootme](https://www.root-me.org/?lang=en) or [hackthissite](https://www.hackthissite.org/). For your information, stego is hiding something which can be in the form of text, audio, image, and video into another form of file. There are numerous tools used to extract data from a stego file, you can check [this](https://0xrick.github.io/lists/stego/) and [this](https://github.com/DominicBreuker/stego-toolkit). For this challenge, we are going to try 5 different ways to extract the information from a stego file. Without further ado, let's start the walkthrough.

## Task 1: Simple stego

Something is hiding inside the image, can you find it?

![task 1](/assets/images/THM/2020-08-10-basic-steganography/2.jpg)

I had tried the following ways to extract the data from this image. Let's see the result.

Tool | Result | Remark
-----|--------|--------
strings | Failure | All information is gibberish
exiftool | Failure | Nothing is hiding inside the metadata
zsteg | Failure | File header error
binwalk | Failure | Can't detect the hidden file
steghide | Success | -

Look like we strike a goal by using the [steghide](http://steghide.sourceforge.net/). To extract the data using steghide, use the following command without any passphrase.

```
steghide extract -sf Challenge1.jpg
```

![task 1 answer](/assets/images/THM/2020-08-10-basic-steganography/3.png)

You just get your first flag. However, the next challenges gonna take you a long time to solve it, how about listening to a song?

[youtube](https://www.youtube.com/watch?v=dQw4w9WgXcQ)

## Task 2: Cracking the password

In the previous task, we have successfully extracted the flag using steghide. How about this one?

![task 2](/assets/images/THM/2020-08-10-basic-steganography/4.jpeg)

Once again, launch your steghide without the passphrase.

![steghide fail](/assets/images/THM/2020-08-10-basic-steganography/5.png)

Oops, look like we need the passphrase to extract the flag within it. After searching across the stego tool list, I come across with a steghide password cracker called [stegcracker](https://github.com/Paradoxis/StegCracker). We are going to crack the password by using [rockyou.txt wordlist](https://github.com/brannondorsey/naive-hashcat/releases/download/data/rockyou.txt). Enter the following command to crack the password.

```
stegcracker Challenge2.jpeg rockyou.txt
```

Now, take a break, have a coffee or watch a movie. This cracking process takes 2 to 3 hours for my Intel-i3 gen-2 laptop. If everything runs smoothly, you should get the following result.

![task 2 result](/assets/images/THM/2020-08-10-basic-steganography/6.png)

The passphrase for the file is **Passp0rt**. Yup, the time and electricity I spent is definitely worth it.

## Task 3: Crack and decode

Can you find the flag?

![task 3](/assets/images/THM/2020-08-10-basic-steganography/7.jpg)

Similar to the previous task, you need to crack the password in order to extract the flag from the image file. This time, it took less than 10 seconds to crack the password. Huh... something not right.

![password](/assets/images/THM/2020-08-10-basic-steganography/8.png)

What a simple password. Next, punch in the password and get the flag.

![bases](/assets/images/THM/2020-08-10-basic-steganography/9.png)

For your information, this is an encoding flag using a type of base. It can be base58, base64, base85 or even base91. Which one could it be?

![base 64](/assets/images/THM/2020-08-10-basic-steganography/10.png)

Is a base64. However, something still not right. The flag is unreadable! Look like we have the mess with the alphabet order. Time to call the all-mighty Ceasar. (Cough), is [Ceasar cipher](https://cryptii.com/pipes/caesar-cipher).

![ceaser](/assets/images/THM/2020-08-10-basic-steganography/11.png)

A Ceasar cipher +16 solved the challenge.

## Conclusion

That's all for the basic steganography, cracking and decoding challenges. Hope you learn something today and see you later ;).
