---
layout: post
permalink: /posts/ctflearn/binary-easy
title: "CTFLearn write-up: Binary (Easy)"
date: 2020-08-15 18:12
tags: ctflearn CTF binary
description: "Today, we are going for an easy binary challenge. For your information, there is only 1 task on easy mode, it going to be a short walkthrough."
---

Hello there, welcome to another CTFLearn walkthrough. Today, we are going for an easy binary challenge. For your information, there is only 1 task on easy mode, it going to be a short walkthrough. Without further ado, let see the question

## 1) LAZY GAME CHALLENGE

[Link: https://ctflearn.com/challenge/691](https://ctflearn.com/challenge/691)

![question](/assets/images/ctflearn/2020-08-13-binary-easy/1.png)

First and foremost, connect the server using Netcat just like the description told.

![game](/assets/images/ctflearn/2020-08-13-binary-easy/2.png)

You will be then greeted with the rule of the challenge. Type Y.

![bet](/assets/images/ctflearn/2020-08-13-binary-easy/3.png)

If order to break the rule, you need to enter a negative value. **-1000000** will do. After that keep guessing a number bigger than 10 which guarantees to lose for the entire bet. At the end of the challenge, a flag will be presented to you.

![answer](/assets/images/ctflearn/2020-08-13-binary-easy/4.png)

Minus minus is a plus, that is basic arithmetic. Simple huh? For your information, this is a python written challenge and you can access the source code right [here](https://repl.it/@ragsdale/Lazy-Game-Challenge-1).

## Conclusion

That's all fo rthe simple binary challenge, hope you like it ;).
