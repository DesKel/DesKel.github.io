---
layout: post
permalink: /posts/challengeland/steganography
title: "Challenge Land write-up: Steganography"
date: 2020-08-12 20:48
tags: ChallengeLand CTF steganography
description: Welcome to another challenge land write up Today, we are going to finish off all four steganography challenges."
---

Greeting! Welcome to another challenge land write up Today, we are going to finish off all four steganography challenges. There is one particular challenge that caught my eye which is the first challenge. This is my first time encounter such kind of interesting problem. I'm going to use it for my next CTF room in THM. Also, make sure you slay the correct enemy. Without further ado, let's begin with our challenge.

![target](/assets/images/challengeland/2020-08-12-steganography/1.png)

## Steganography 1

Download the image and start our very first stego task.

![stego 1](/assets/images/challengeland/2020-08-12-steganography/2.jpeg)

Like I said before, this challenge is a little bit unique. In order to complete this task, we need to do a reverse image search using [TinEye](https://www.tineye.com/).

![tineye](/assets/images/challengeland/2020-08-12-steganography/3.png)

Look like we have plenty of similar image on the internet. Simply download an image and we are going to compare the original with the image with stego text.

```
diff -a image1.jpeg ori.jpg | hexdump -C
```

![diff](/assets/images/challengeland/2020-08-12-steganography/4.png)

Are you able to distinguish the difference?

## Steganography 2

Download the image and you get a similar image as stego 1.

![stego 2](/assets/images/challengeland/2020-08-12-steganography/5.jpeg)

![binwalk](/assets/images/challengeland/2020-08-12-steganography/6.png)

Well, we have an image file within an image file. To extract all the contents within the file, I'm going to use binwalk with the following command.

```
binwalk --dd='.*' image2.jpeg
```

![stego 2 solution](/assets/images/challengeland/2020-08-12-steganography/7.png)

A hidden message inside the image. The flag is the message.

## Steganography 3

You get a similar picture.

![stego 3](/assets/images/challengeland/2020-08-12-steganography/8.jpeg)

This one easy, use strings command and finish off the challenge.

![strings]((/assets/images/challengeland/2020-08-12-steganography/9.png)

## Steganography 4

I guess I don't need to say anything about this.

![stego 4](/assets/images/challengeland/2020-08-12-steganography/10.jpeg)

Similar to task 2 but a little bit advance. Extract all the files and read the XML using strings command. You will eventually locate the following flag.

![read it](/assets/images/challengeland/2020-08-12-steganography/11.png)

## Conclusion

That's all for the quick and simple steganography challenge. Hope you like it. Until next time.
