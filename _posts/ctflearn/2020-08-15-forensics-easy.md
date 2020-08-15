---
layout: post
permalink: /posts/ctflearn/forensics-easy
title: "CTFLearn write-up: Forensics (Easy)"
date: 2020-08-15 18:12
tags: ctflearn CTF forensics
description: "Welcome to another CTFLearn write-up. Today, we will go through the easy Forensics and most of the tasks contain basic steganography. Enjoy!"
---

Greeting there, welcome to another CTFLearn write-up. Well, it has been a while since my last walkthrough on the binary and cryptography. So, I'm going to do more bundle walkthrough on the CTFLearn. As for today, we will go through the easy Forensics and most of the tasks contain basic steganography. Enjoy!

## 1) Forensics 101

[Link: https://ctflearn.com/challenge/96](https://ctflearn.com/challenge/96)

![forensic 101](/assets/images/ctflearn/2020-08-15-forensics-easy/1.jpg)

If you are a Linux user, use strings command. E.g.

```
strings minion.jpg
```

![forensic 101 flag](/assets/images/ctflearn/2020-08-15-forensics-easy/2.png)

This is the easiest way to hide your data inside the image.

## 2) Taking LS

[Link: https://ctflearn.com/challenge/103](https://ctflearn.com/challenge/103)

I guess this is the easiest task in the entire forensics. You don't need any prior knowledge of extracting the flag. Simply unzip the file, read the password and extract the PDF.

![taking ls](/assets/images/ctflearn/2020-08-15-forensics-easy/3.png)

![taking ls flag](/assets/images/ctflearn/2020-08-15-forensics-easy/4.png)

## 3) Binwalk

[Link: https://ctflearn.com/challenge/108](https://ctflearn.com/challenge/108)

For this task, you are required to use a stego tool called [binwalk](https://github.com/ReFirmLabs/binwalk). For Linux (Ubuntu or Kali) user. install the tool with the following command.

```
sudo apt-get install binwalk
```

Let's find out what is inside the image using the binwalk.

![binwalk](/assets/images/ctflearn/2020-08-15-forensics-easy/5.png)

Well, well, well. We have a hidden PNG image inside another PNG image. You can use --extract option to extract the files but I prefer adding --dd flag to extract all files. The command will look like this.

```
binwalk --extract --dd=".*" PurpleThing.jpeg
```

Read the hidden PNG inside the extracted directory/folder.

![binwalk answer](/assets/images/ctflearn/2020-08-15-forensics-easy/6.png)

## 4) WOW.... So Meta

[Link: https://ctflearn.com/challenge/348](https://ctflearn.com/challenge/348)

You need another stego tool called [ExifTool](https://exiftool.org/). This tool used to extract all the meta information from an image. This information can be the timestamp, location of the image being captured, software information and even sensitive data. Simply punch in the following command to extract the flag. (For Linux)

```
exiftool image.jpg
```

![meta answer](/assets/images/ctflearn/2020-08-15-forensics-easy/7.png)

## 5) A CAPture of a Flag

[Link: https://ctflearn.com/challenge/356](https://ctflearn.com/challenge/356)

This task could be one of the hardest in the easy forensics category. You are required to use [Wireshark](https://www.wireshark.org/download.html) to read the packet file. In the Wireshark, try to read the packet in the TCP stream. You can do this by right-click ant TCP or HTTP packet and locate to file --> TCP stream. As shown in the figure below.

![wireshark](/assets/images/ctflearn/2020-08-15-forensics-easy/8.png)

After that, locate stream 5 on the HTTP request, you should find something interesting.

![encode flag](/assets/images/ctflearn/2020-08-15-forensics-easy/9.png)

The message actually encoded with base64. Decode it with an online tool or Linux command.

![wireshark flag](/assets/images/ctflearn/2020-08-15-forensics-easy/10.png)

## Conclusion

That's all for the easy forensic on the CTFlearn. The new write-up will be added to this post if I found any. I hope you learn something new, until next time ;).
