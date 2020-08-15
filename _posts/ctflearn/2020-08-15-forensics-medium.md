---
layout: post
permalink: /posts/ctflearn/forensics-medium
title: "CTFLearn write-up: Forensics (Medium)"
date: 2020-08-15 18:47
tags: ctflearn CTF forensics
description: "Another welcome to another CTFlearn write-up. As for today, we are going to walk through the Medium Lebel forensics."
---

Hello there, another welcome to another CTFlearn write-up. As for today, we are going to walk through the Medium level forensics. Let's do a quick start.

## 1) 07601

[Link: https://ctflearn.com/challenge/97](https://ctflearn.com/challenge/97)

This one is simple. First of all, let's check the hidden files using the binwalk.

![binwalk](/assets/images/ctflearn/2020-08-15-forensics-medium/1.png)

We have a lot of stuff inside the image file. Without thinking twice, extract all the files with the following command.

```
binwalk --extract --dd=".*" AGT.png
```

The flag is hidden inside the " I warned you.jpg' file. By checking the file type, it is a data file instead of a jpeg.

![strings](/assets/images/ctflearn/2020-08-15-forensics-medium/2.png)

Use a command like 'strings' to read the flag.

![07601 flag](/assets/images/ctflearn/2020-08-15-forensics-medium/3.png)

## 2) Git Is Good

[Link: https://ctflearn.com/challenge/104]

First of all, extract the file and read the log.

![the git](/assets/images/ctflearn/2020-08-15-forensics-medium/4.png)

The flag is hidden on the second commit. Use git show to reveal the flag.

![git flag](/assets/images/ctflearn/2020-08-15-forensics-medium/5.png)

## 3) Up For A Little Challenge?

[Link: https://ctflearn.com/challenge/142](https://ctflearn.com/challenge/142)

For this task, you have to look really deep. First and foremost, locate a MEGA URL inside the download image. (Using strings command)

![another string](/assets/images/ctflearn/2020-08-15-forensics-medium/6.png)

By visiting the MEGA URL, you will get a ZIP file.

![zip file](/assets/images/ctflearn/2020-08-15-forensics-medium/7.png)

Extract the zip file and ignore the 'Loo Nothing Becomes Useless ack' as it has nothing to do with the challenge. There is one password-protected zip file.

![cerb4](/assets/images/ctflearn/2020-08-15-forensics-medium/8.png)

The extension is a cover-up.

![coverup](/assets/images/ctflearn/2020-08-15-forensics-medium/9.png)

Problem is, where is the password? The password is located at the **first downloaded picture where you find the mega URL**. (Nothing Is As It Seems)

![image pass](/assets/images/ctflearn/2020-08-15-forensics-medium/10.png)

Another image is extracted from the zip. The flag is located at the bottom-right corner.

![skeleto](/assets/images/ctflearn/2020-08-15-forensics-medium/11.png)

![challenge flag](/assets/images/ctflearn/2020-08-15-forensics-medium/12.png)

Hopefully, you can see the flag.

## 4) Milk's Best Friend

[Link: https://ctflearn.com/challenge/195](https://ctflearn.com/challenge/195)

Similar to the first task, binwalk the oreo.jpg

![binwalk](/assets/images/ctflearn/2020-08-15-forensics-medium/13.png)

Extract the file with the binwalk.

```
binwalk --extract --dd=".*" oreo.jpg
```

After extracting the files, there is another oreo image (2 pieces of oreo). Use 'strings' command to locate the flag.

![milk flag](/assets/images/ctflearn/2020-08-15-forensics-medium/14.png)

## 5) Digital Camouflage

[Link: https://ctflearn.com/challenge/237](https://ctflearn.com/challenge/237)

Open up the PCAP file with Wireshark and follow the TCP stream to frame 3.

![pcap](/assets/images/ctflearn/2020-08-15-forensics-medium/15.png)

The password is encoded with base64 and make sure to change the URL encoded padding (%3D) to '='.

![camo flag](/assets/images/ctflearn/2020-08-15-forensics-medium/16.png)

## 6) Dumpster

[Link: https://ctflearn.com/challenge/355](https://ctflearn.com/challenge/355)

This is one of the toughest challenges I faced. This is because I'm not really good at Java programming. So, all credits go to this [youtube video](https://www.youtube.com/watch?v=HYiqCjKRs70). First off, open up the dumpster with the [visualvm](https://visualvm.github.io/). After that, find the passHash in the dump.

![visualvm](/assets/images/ctflearn/2020-08-15-forensics-medium/17.png)

Make sure you have selected the thread. After that, I've drafted the following Java code.

```Java
import java.security.MessageDigest;
import java.util.Arrays;
import java.util.Base64;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;

public class Decryptor
{
	public static final String FLAG = "S+kUZtaHEYpFpv2ixuTnqBdORNzsdVJrAxWznyOljEo=";

	public static byte[] decrypt(byte[] msg, byte [] passHash) throws Exception
	{
		SecretKeySpec spec = new SecretKeySpec(passHash, "AES");
		Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
		cipher.init(Cipher.DECRYPT_MODE, spec);
		return cipher.doFinal(msg);
	}

	public static void main(String[] args) throws Exception
	{
		byte[] passHash = {7, 95, -34, 16, -89, -86, 73, 108, -128, 71, 43, 41, 100, 40, 53, -24};
		System.out.println(new String(decrypt(Base64.getDecoder().decode(FLAG.getBytes()),passHash)));
	}
}
```

Save it as Decryptor.java and run it with the following command.

```
java Decryptor.java
```

![dumper flag](/assets/images/ctflearn/2020-08-15-forensics-medium/18.png)

## 7) The adventures of Boris Ivanov. Part 1.

[Link: https://ctflearn.com/challenge/373](https://ctflearn.com/challenge/373)

Download the PDF file. No binwalk or steghide for this task, just a normal stereogram. I used [stegsolve](https://github.com/zardus/ctf-tools/tree/master/stegsolve) tool to complete this challenge.

![stegosolver](/assets/images/ctflearn/2020-08-15-forensics-medium/19.png)

keep pushing the image to left (press right key), you should get the flag at offset 102.

![boris 1 flag](/assets/images/ctflearn/2020-08-15-forensics-medium/20.png)

## 8) Exclusive Santa

[Link: https://ctflearn.com/challenge/851](https://ctflearn.com/challenge/851)

We have two files from the challenge. One is a **distorted image** and the other is a **normal weird image**. As the title suggested, the distorted image is somehow XOR between 2 pictures. Our first task is to find one of the picture and XOR it to find another image.

By using the binwalk on the normal image, you will come across the following.

![binwalk](/assets/images/ctflearn/2020-08-15-forensics-medium/21.png)

We got another image inside 3.png. Extract all the files within the image, we find what we needed.

![GoT](/assets/images/ctflearn/2020-08-15-forensics-medium/22.png)

Xor the extracted image with the distorted image with [stegsolve](https://github.com/zardus/ctf-tools/tree/master/stegsolve).

![combine](/assets/images/ctflearn/2020-08-15-forensics-medium/23.png)

![santa flag](/assets/images/ctflearn/2020-08-15-forensics-medium/24.png)

## 9) F1L3 M1X3R 2 - MP4 Identity Issue

(In progress)
