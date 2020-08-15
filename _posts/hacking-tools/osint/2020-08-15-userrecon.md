---
layout: post
permalink: /posts/hacking-tools/osint/userrecon
title: "Des's review: [OSINT] UserRecon"
date: 2020-08-15 22:28
tags: review osint
description: "This is an OSINT tool that searches the given username across 75 social media by using the CURL command."
---

![introductory](/assets/images/hacking-tools/osint/2020-08-15-userrecon/1.png)

[Link: https://github.com/thelinuxchoice/userrecon](Link: https://github.com/thelinuxchoice/userrecon)

This is an OSINT tool that searches the given username across 75 social media by using the CURL command. The script is written in a simple bash and currently only supports Linux. However, the tool is not so accurate as it is seen. Since the basic mechanism of the tool is to pull a page using the curl command. Hence, even some the website having a legit 404 status, it still manage to return status 1 to the curl (false alert). Overall is good, at least we can probe what user is on the internet.

## Des's review

### The pro
1. Probing the user on the internet with a single username.
2. Heavily depends on social media and blogging sites.

### The con
1. The script is written in curl command, a big chance on a false alarm.
2. Only support Linux due to curl command.

**Des's score: 2.5/5 (An average OSINT tool with high false alarm rate)**
