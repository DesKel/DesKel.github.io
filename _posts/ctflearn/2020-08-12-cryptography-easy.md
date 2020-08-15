---
layout: post
permalink: /posts/thm/cryptography-easy
title: "CTFLearn write-up: Cryptography (Easy)"
date: 2020-08-15 18:12
tags: ctflearn CTF cryptography
description: "This is a whole new CTF series. For this post, I'm am going to walk through all the easy level cryptography."
---

[Link: https://ctflearn.com](https://ctflearn.com)

Good news guys, I'm going to do a brand new CTF series. The site is called CTFLearn, another site to sharpen up your hacking skill. Just like hackthissite and challenge land, you need to complete the task and get the point. The pro of this site is the challenges are marked from easy to hard. If you are new to CTF, this might be a good site to start with. For this post, I'm am going to walk through all the easy level cryptography.

## 1) HEXTROADINARY

[Link: https://ctflearn.com/problems/158](https://ctflearn.com/problems/158)

This is not only a hex. If you looked at the description, it mentioned ROXy. Basically this is a xor and hex cryptograph. You need XOR 0xc4115 and 0x4cf8 in order to get the flag. Use the [following tool](http://xor.pw/#) and reveal the flag.

![hextrordinary](/assets/images/ctflearn/2020-08-12-cryptography-easy/1.png)

## 2) BASE 2 2 THE 6

[Link: https://ctflearn.com/problems/192](https://ctflearn.com/problems/192)

The given ciphertext is Q1RGe0ZsYWdneVdhZ2d5UmFnZ3l9. Hint on the title, this is a base64 encoded text. Easy!

![base 2 2 the 6](/assets/images/ctflearn/2020-08-12-cryptography-easy/2.png)

## 3) BRUXOR

[Link: https://ctflearn.com/problems/227](https://ctflearn.com/problems/227)

This is one of my favorites cryptograph. The given ciphertext is  q{vpln'bH_varHuebcrqxetrHOXEj . Judging from the title, we need to Bruteforce the ciphertext by using XOR. Xortool might come in handy for this challenge. But before that, I need to convert the text into hex format and punch in the following command

```
xortool -x -b xor.hex
```

After that, read the summary of the output file and search for the decoded text with 100% charset validation.

![validation](/assets/images/ctflearn/2020-08-12-cryptography-easy/3.png)

You will eventually get the flag.

![bruxor](/assets/images/ctflearn/2020-08-12-cryptography-easy/4.png)

## 4) VIGENERE CIPHER

[Link: https://ctflearn.com/problems/305](https://ctflearn.com/problems/305)

The given ciphertext and key are gwox{RgqssihYspOntqpxs} and blorpy, respectively. Follow the title and decode the text using [Vigenere cipher](https://cryptii.com/pipes/vigenere-cipher).

![vigenere cipher](/assets/images/ctflearn/2020-08-12-cryptography-easy/5.png)

## 5) Morse code

[Link: https://ctflearn.com/problems/309](https://ctflearn.com/problems/309)

Like the title suggest, decode the ciphertext using [morse code translator](https://www.dcode.fr/morse-code).

![morse code](/assets/images/ctflearn/2020-08-12-cryptography-easy/6.png)

## 6)  HYPERSTREAM TEST #2

[Link: https://ctflearn.com/problems/443](https://ctflearn.com/problems/443)

Hint on the description. This is a [bacon cipher](https://mothereff.in/bacon), believe it or not.

![hyperstream test 2](/assets/images/ctflearn/2020-08-12-cryptography-easy/7.png)

## 7) Character Encoding

[Link: https://ctflearn.com/challenge/115](https://ctflearn.com/challenge/115)

This one is easy. Convert the [hex into the ASCII](https://www.rapidtables.com/convert/number/hex-to-ascii.html).

![character encoding](/assets/images/ctflearn/2020-08-12-cryptography-easy/8.png)

## 8) Reverse Polarity

[Link: https://ctflearn.com/challenge/230](https://ctflearn.com/challenge/230)

Another simple task, convert to [binary into ASCII](https://www.rapidtables.com/convert/number/binary-to-ascii.html).

![reverse polarity](/assets/images/ctflearn/2020-08-12-cryptography-easy/9.png)

## Conclusion

That's all for the CTFlearn cryptography easy level write-up. Hope you enjoy it. See ya ;)
