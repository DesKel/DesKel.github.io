---
layout: post
permalink: /posts/thm/stegosaurus
title: "THM write-up: STEGOsaurus"
date: 2020-08-11 20:07
tags: tryhackme steganography
description: "Howdy, welcome to another tryhackme CTF write-up. Today, we are going for a super short and yet tricky stego challenge."
---

![titlecard](/assets/images/THM/2020-08-11-stegosaurus/1.png)

[Link: https://tryhackme.com/room/stegosaurus](https://tryhackme.com/room/stegosaurus)

Howdy, welcome to another tryhackme CTF write-up. Today, we are going for a super short and yet tricky stego challenge. This challenge is much easier than you thought providing you not getting troll by the creator of the room, Brandon. Yup, the one who creates the "You can't solve it" room. I started to like this guy. Alright, let's get the challenge on.

## Task 1: What is inside the picture

Your task is to find the hidden image and the flag inside a meme picture.

![meme](/assets/images/THM/2020-08-11-stegosaurus/2.webp)

Awwwwwww~~~ cute doggy.

### Task 1-1: Extract the file

This task is easy and I guess everyone knows that. The only tool you need is Steghide.

```
steghide extarct -sf doggy.jpg
```

![command](/assets/images/THM/2020-08-11-stegosaurus/3.png)

![panda](/assets/images/THM/2020-08-11-stegosaurus/4.png)

### Task 1-2: Stegcracker?

You though you can finish this challenge using stegcracker? Pfttt, NEVER EVER TRUST THE DESCRIPTION. I admit that I have been troll hard by this challenge. You don't need a single Kali tool to solve this one. You just need to adjust the exposure of the image. Stego is hiding data within an image and there is no fixed method like Steghide. This is the picture after tunning the exposure down.

![troll](/assets/images/THM/2020-08-11-stegosaurus/5.png)

I'm done~~~~~~~~~~~. Please, save the planet, our world is dying

## Conclusion

Well, that's all for the short write-up. Hope you enjoy it and don't forget to save the planet by recycling, reduce carbon usage and etc. Until next time ;)
