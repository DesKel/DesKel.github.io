---
layout: post
permalink: /posts/thm/programming-easy
title: "CTFLearn write-up: Programming (Easy)"
date: 2020-08-15 18:12
tags: ctflearn CTF programming
description: "Howdy there, welcome to another CTFLearn write-up. Today, we are going through an easy programming challenge."
---

Howdy there, welcome to another CTFLearn write-up. Today, we are going through an easy programming challenge. For the entire programming challenge, I'm going to use python programming. You also can use C, C++, Java or even Javascript to solve the challenge.

## 1) Simple Programming

[Link: https://ctflearn.com/challenge/174](https://ctflearn.com/challenge/174)

Copy the following script and run it with python 2 or 3. All the explanations are on the script.

```
# initiate the parameters
count = 0
file = 'data.dat'

with open(file) as f:    #Open the file
        l = f.readlines()   #read file by line
        for line in l:
                zero = line.count('0')  #count number of zero in the line
                one = line.count('1')   #count number of one in the line
                '''the condition where the number of '0' is divisible by 3
                OR the number of '1' is divisible by 2'''
                if (zero%3 == 0) or (one%2 == 0):
                        count = count + 1

print("Number of lines: " + str(count))
f.close()
```

![simple programming ans](/assets/images/ctflearn/2020-08-15-programming-easy/1.png)

## Conclusion

That's all for the simple programming on CTFlearn. The post will be updated once I found another new task. See ya :) 
