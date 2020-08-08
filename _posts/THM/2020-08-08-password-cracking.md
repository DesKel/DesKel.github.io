---
layout: post
permalink: /posts/thm/password-cracking
title: "THM write-up: Password Cracking"
date: 2020-08-08 11:30
tags: tryhackme hash ophcrack
description: "This walkthrough will heavily depend on the hashcat and ophcrack tool. ophcrack is basically a window password cracker."
---

![titlecard](/assets/images/THM/2020-08-08-password-cracking/1.png)

[Link: https://tryhackme.com/room/passwordcracking](https://tryhackme.com/room/passwordcracking)

On the [last post](https://embeddedworld.home.blog/2019/05/11/hacking-walk-through-cracking-the-hashes/), I talked about using the [hashcat](https://hashcat.net/hashcat/) to crack various type of hashes. This walkthrough will heavily depend on the hashcat and ophcrack tool. [ophcrack](http://ophcrack.sourceforge.net/) is basically a window password cracker based on the rainbow table. Without further ado, let's begin the walkthrough.

## Task 1: Brute force attack (MD5)

This time we are not going to use any dictionary to crack the hashed and brute force attack is used instead.

### Part 1:  3 digits brute force

Simply punch in the following command (for window 64-bit):

```
hashcat64.exe -D 2 -m 0 Hash/hash.txt -a 3 TRY-HACK-ME-?d?d?d
```

- -D 2 : Choose GPU as the main resource to crack the hash 
- -m 0: Loaded with MD5 hash 
- -a 3: Brute force mode
- ?d?d?d: mask that indicate 3 digits to be brute force with (000-999)

All the brute forced mask can be explained as below:

- ?l = abcdefghijklmnopqrstuvwxyz 
- ?u = ABCDEFGHIJKLMNOPQRSTUVWXYZ
- ?d = 0123456789
- ?s =  All special symbols
- ?a = ?l?u?d?s
- ?b = 0x00 - 0xff

### Part 2: 4 digits brute force

Similar to the part 1, you need to add extra one mask in the command:

```
hashcat64.exe -D 2 -m 0 Hash/hash.txt -a 3 TRY-HACK-ME-?d?d?d?d
```

### Part 3: 5 digits brute force

Similar to part 1 and 2, 5 digits mask is needed:

```
hashcat64.exe -D 2 -m 0 Hash/hash.txt -a 3 TRY-HACK-ME-?d?d?d?d?d
```

## Task 2: Combination attack (MD5)

The combination attack in this context is using both dictionary and brute forcing attack. The dictionary is given for this challenge and how we perform a combination attack? 

### Part 1: US city dictionary+ 2 digits brute force

To perform a combination attack, simply change the mode (-a) to 6. The command for the attack is shown on below:

```
hashcat64.exe -D 2 -m 0 Hash/hash.txt -a 6 Dict/us-city.txt ?d?d
```

### Part 2: US city dictionary + color dictionary + 3 digits brute force

This part is a bit tricky, you need to combine/join both dictionary into 1 because the attack mode (-a 6) only can take 2 arguments. To combine the dictionaries, you are required to download the hashcat-util for the combinator executable file. After that, combine two dictionaries by simply punch in this command: 

```
combinator.exe us-city.txt color.txt > cityColor.txt
```

Now, you get a new dictionary called cityColor.txt (I'm copied it to Dict directory). After that, crack the hash using the following command:

```
hashcat64.exe -D 2 -m 0 Hash/hash.txt -a 6 Dict/cityColor.txt ?d?d?d
```

### Part 3: Color dictionary + country dictionary + 4 digits brute force

Similar to part 2, combine the dictionaries using the combinator.exe and then crack the hash using the following command:

```
hashcat64.exe -D 2 -m 0 Hash/hash.txt -a 6 Dict/colorCountry.txt ?d?d?d?d
```

## Task 3: NTLM rainbow table

This task is straight forward. Download the [ophcrack](http://ophcrack.sourceforge.net/)  and the table ([XP special, 8.0GB](https://sourceforge.net/projects/ophcrack/files/tables/XP%20special/)). Yes, is 8.0GB, download it if you have any spare data or your data plan is absolutely unlimited.  

![NTLM](/assets/images/THM/2020-08-08-password-cracking/2.png)

## Conclusion

That's all for the walkthrough. Hope you learned something new. Have a nice day :)