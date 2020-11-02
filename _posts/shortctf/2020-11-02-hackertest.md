---
layout: post
permalink: /posts/shortctf/hackertest
title: "Short CTF: hackertest"
date: 2020-11-02 18:04
tags: php js critical_thinking
description: "Hackertest  is an online hacker simulation with 20 different levels. Each level require a unique skill to complete with."
---

![logo](/assets/images/shortctf/hackertest/logo.png)

[Hackertest](http://www.hackertest.net/) is an online hacker simulation with 20 different levels. Each level requires a unique skill to complete with. At the end of the challenge, you should have you JS, PHP, HTML, and even critical thinking skill getting improved. Have fun!

- [Level 1](#1)
- [Level 2](#2)
- [Level 3](#3)
- [Level 4](#4)
- [Level 5](#5)
- [Level 6](#6)
- [Level 7](#7)
- [Level 8](#8)
- [Level 9](#9)
- [Level 10](#10)
- [Level 11](#11)
- [Level 12](#12)
- [Level 13](#13)
- [Level 14](#14)
- [Level 15](#15)
- [Level 16](#16)
- [Level 17](#17)
- [Level 18](#18)
- [Level 19](#19)
- [Level 20](#20)

<span id="1"></span>

## Level 1

![Level 1 question](/assets/images/shortctf/hackertest/1_1.png)

The first level's password is located inside the JS script source code. Remember, the parameter of **variable a** is declared as some sort ASCII, do not confuse with the real **NULL**

![Level 1 source](/assets/images/shortctf/hackertest/1_2.png)

Parse the parameter and proceed to next Level.

<span id="2"></span>

## Level 2

![Level 2 question](/assets/images/shortctf/hackertest/2_1.png)

On the first arrival, you will be greeted by a password text box. Simply ignore the text box by clicking **cancel** and check the source code.

![Level 2 source](/assets/images/shortctf/hackertest/2_2.png)

Similar to the previous level, the password is located inside the script. Refresh the page and enter the password.

<span id="3"></span>

## Level 3
![Level 3 question](/assets/images/shortctf/hackertest/3_1.png)

Yet another text box, guess you knew the drill. Ignore the text box by clicking **cancel**. After that, check the source code.

![Level 3 source](/assets/images/shortctf/hackertest/3_2.png)

The password is on the **pw** variable and somehow we need to know the value of alinkColor. The task can be easily solved by using a console, simply type

```javascript
window.document.alinkColor;
```

![Level 3 console](/assets/images/shortctf/hackertest/3_3.png)

The link color is black.

<span id="4"></span>

## Level 4

![Level 4 question](/assets/images/shortctf/hackertest/4_1.png)

Level 4 is skippable.

<span id="5"></span>

## Level 5

![Level 5 question](/assets/images/shortctf/hackertest/5_1.png)

For this level,  you can't simply ignore the text box where it will take you back to the previous stage if you try to ignore it. There is numerous way to solve this challenge and my approach is using **curl command**.

![Level 5 curl](/assets/images/shortctf/hackertest/5_2.png)

<span id="6"></span>

## Level 6

![Level 6 question](/assets/images/shortctf/hackertest/6_1.png)

As usual, ignore the text box and check the source code.

![Level 6 code](/assets/images/shortctf/hackertest/6_2.png)

Guess what! The password is inside the .js file. That is all you need to know.

<span id="7"></span>

## Level 7

![Level 7 question](/assets/images/shortctf/hackertest/7_1.png)

A login form, cool! If you are going to brute-force or using sqlmap on the login form, you are going way too far. The answer is in the source code which can be missed easily.

![Level 7 source](/assets/images/shortctf/hackertest/7_2.png)

Yes, I'm talking about the GIF file. The credential is within the file, bottom right.

<span id="8"></span>

## Level 8

![Level 8 question](/assets/images/shortctf/hackertest/8_1.png)

Another login form and this time nothing can be missed in the source code or does it? If you try to login with the wrong credential, you will be present with a page.

![Level 8 error](/assets/images/shortctf/hackertest/8_2.png)

Check the source code and you will notice something familiar.

![Level 8 code](/assets/images/shortctf/hackertest/8_3.png)

![Level 8 hint](/assets/images/shortctf/hackertest/8_4.png)

After that, look at the bottom right. a hint about .psd file. The file can be download using the following url.

```
http://www.hackertest.net/images/phat.psd
```

By using an [online photoshop tool](https://www.photopea.com/), remove all the watermark to reveal the credential which located on the bottom right.

![Leve; 8 PS](/assets/images/shortctf/hackertest/8_5.png)

<span id="9"></span>

## Level 9

![Level 9 question](/assets/images/shortctf/hackertest/9_1.png)

Level 9 is rather an easy level throughout the entire hackertest. The password is encoded in base64 and somehow located at the bottom of the source code.

![Level 9 code](/assets/images/shortctf/hackertest/9_2.png)

Decode the base64 and the next Level challenge is located at

```
http://www.hackertest.net/(decoded base64).php
```

<span id="10"></span>

## Level 10

![Level 10 question](/assets/images/shortctf/hackertest/10_1.png)

Look, we got a brand new interface. First of all, do not let the instruction fool you out as critical thinking skill is required to solve this challenge. If you tried to look at the description inside the source code,  something is off.

![Level 10 code](/assets/images/shortctf/hackertest/10_2.png)

Some of the word or letter is italic. Combine those letters and you should obtain the password for the challenge.

Note: The password is in lower case, including the first letter.

![Level 10 question 2](/assets/images/shortctf/hackertest/10_3.png)

What's happening? An empty page? Tried check with the source code.

![Level 10 next level](/assets/images/shortctf/hackertest/10_4.png)

Visit the hidden page for next level.

<span id="11"></span>

## Level 11

![Level 11 question](/assets/images/shortctf/hackertest/11_1.png)

What are you looking at? Source code?

![Level 11 code](/assets/images/shortctf/hackertest/11_2.png)

Yup, inside the source code.

<span id="12"></span>

## Level 12

![Level 12 question](/assets/images/shortctf/hackertest/12_1.png)

If you compared the logo to the previous page, we have a JPG logo instead of a GIF. Those are the 3 letters mentioned on the page. Something must be hidden inside the JPG file.

![Level 12 jpg](/assets/images/shortctf/hackertest/12_2.png)

Playing around with the contrast and shadow. You'll notice there is something on the Russian continent. It is a bad Spanish word.

<span id="13"></span>

## Level 13

![Level 13 question](/assets/images/shortctf/hackertest/13_1.png)

Similar to the previous level, check the hidden .php inside the given image. The image needs to investigate is the word 'Level 13' itself.

![Level 13 pic](/assets/images/shortctf/hackertest/13_2.png)

An XML file huh. Well, the next level hint is inside the file.

![Level 13 XML](/assets/images/shortctf/hackertest/13_3.png)

<span id="14"></span>

## Level 14

![Level 14 question](/assets/images/shortctf/hackertest/14_1.png)

I'm freaking love this level because I was getting troll so hard by the advertisement GIF. You can either wait for 20 minutes for the gif to show you the answer or simply complete the challenge using [GIMP](https://www.gimp.org/).

![Level 14 GIMP](/assets/images/shortctf/hackertest/14_2.png)

The next level PHP is on frame 6 which only shows after 20 minutes of static animation. The next level is **totally.php**

<span id="15"></span>

## Level 15

![Level 15 question](/assets/images/shortctf/hackertest/15_1.png)

Upon clicking the link, we will receive a broken JPGimage. After investigating the image using hex edit, the header and footer of the image are correct. However, the content seems to be corrupted and there are two hints on the broken JPG.

- Ducky
- Level 16: unavailable

![level 15 hex](/assets/images/shortctf/hackertest/15_2.png)

Ducky.php does not yield any good result. However, **/unavailable** (without extension) lead to the following page

![Level 15 unavailable](/assets/images/shortctf/hackertest/15_3.png)

As for the source code

![Level 15 image](/assets/images/shortctf/hackertest/15_4.png)

I'm guess level 16 is not actually broken after all. It just another trick.

<span id="16"></span>

## Level 16

![Level 16 question](/assets/images/shortctf/hackertest/16_1.png)

An empty page! Let see what is inside the source code.

![Level 16 code](/assets/images/shortctf/hackertest/16_2.png)

A JPG, let's check that out.

![Level 16 jpg](/assets/images/shortctf/hackertest/16_3.png)

Shoot! Another broken image. Time for another hex edit.

![Level 16 hex](/assets/images/shortctf/hackertest/16_4.png)

The next location is ducky.php under **/unavailable** directory. That is why we can't reach it in the first place.

<span id="17"></span>

## Level 17

![Level 17 question](/assets/images/shortctf/hackertest/17_1.png)

Deja-vu? Actually not. There is a hidden text in white color. You can either highlight the whole page using **ctrl-a** or check the source code.

![Level 17 reveal](/assets/images/shortctf/hackertest/17_2.png)

Just google [your own IP address](https://www.google.com/search?q=my+ip+address) and solve the level. Easy!

Note: Level 18 is on upper level directory which is not inside the **/unavailable** directory.

<span id="18"></span>

## Level 18

![Level 18 question](/assets/images/shortctf/hackertest/18_1.png)

Check the error code at the bottom of the page, eventhough the error is not an actual error.

![Level 18 error](/assets/images/shortctf/hackertest/18_2.png)

<span id="19"></span>

## Level 19

![Level 19 question](/assets/images/shortctf/hackertest/19_1.png)

Well, I can said the level is similar to level 14. Check out the **level20_pass.gif**. GIMP solve everything.

![Level 19 solve](/assets/images/shortctf/hackertest/19_2.png)

0 second show time, you will never get it. The final level is **gazebruh2.htm** Took me some time to brute force it.

<span id="20"></span>

## Level 20

![Level 20 question](/assets/images/shortctf/hackertest/20_1.png)

Time for the final boss. There are few things I wanted to check with.

### ASCII

The ASCII on the page

```
436f6e67726174756c6174696f6e732532312b596f752b686176652b7061737365642b746f2b6c6576656c2b31302e2b486572652532432b7468696e67732b6265636f6d652b6d7563682b6d6f72652b6469666663756c742b2533422d2532395b486f70652b796f752b6765742b7468726f7567682532312b456e6a6f792e
```

is translated as

```
Congratulations%21+You+have+passed+to+level+10.+Here%2C+things+become+much+more+diffcult+%3B-%29[Hope+you+get+through%21+Enjoy.
```

Nothing special, just some encouraging words.

### Base64

This is a multi encoded base64

```
VldwSk5Gb3lVa2hQUjJSclRUSlJlbFJITlU5TlIwNTBWbTE0YTFJelVqSlpNakF4WWtkT2NFNVlWbUZYUmtZeVYycEtTbG95U25SUFZFNU5Xbm93T1QwOT09
```

which decoded as

```
Go to www.streetkorner.net/gb now.
```

By the way, the domain is empty.

### Hidden text

Highlight the entire page using **ctrl-a** or check the source code reveal the hint for the challenge.

![Level 20 hint](/assets/images/shortctf/hackertest/20_2.png)

The hint has something to do with the link we just found out earlier. From

```
www.streetkorner.net/gb
```

to

```
www.hackertest.net/gb22332
```

![level 20 new link](/assets/images/shortctf/hackertest/20_3.png)

We got something out of ordinary, 505 is HTML version not support and I was able to access the site all the time but now? After checking the source code, I found some interesting stuff.

![Level 20 code](/assets/images/shortctf/hackertest/20_4.png)

![Level 20 status code](/assets/images/shortctf/hackertest/20_5.png)

The StatCounter code is within the page. In short, this is not a genuine error page. The status code is 200, not an actual 505. Something is off.

How about

```
www.hackertest.net/505
```

Yes, the 505.

![Level 20 fool](/assets/images/shortctf/hackertest/20_6.png)

Can't fool me this time, the next URL is

```
www.hackertest.net/505/403
```

![Level 20 life](/assets/images/shortctf/hackertest/20_7.png)

The answer is 42, if you google the statement. The next URL is

```
www.hackertest.net/42.php
```

![Complete](/assets/images/shortctf/hackertest/20_8.png)

That's it, we just finished the hackertest. What a journey!
