# AIM Server C (WIP)

An (incomplete) AOL Instant Messager server written in C.

## Table of Contents
- [AIM Server C (WIP)](#aim-server-c-wip)
  - [Table of Contents](#table-of-contents)
  - [About](#about)
    - [Why in C?](#why-in-c)
  - [State of the Union:](#state-of-the-union)
  - [Building](#building)
  - [Disclaimers](#disclaimers)


## About

This is an AOL Instant Messenger server implemented in C. It is horribly inefficient, very incomplete, and most certainly risky to run in any production environment. But it has been an incredibly fun challenge to work on!

### Why in C?

I bounce back and forth between two reasons. 

The first being that C is the language I'm most confortable in as I'm an embedded firmware engineer by trade. 

The second reason being that I wanted a challenge. There are several Go and TypeScript implementations of AIM servers and those languages are much better suited for the task. I felt like writing it in C would be a really fun challenge that would really help me develop my craft.

A bonus third reason, is that I want this to possibly run on older hardware. I have no clue what the original tech stack was for AIM's original servers, but I guarentee it wasn't written in Go. It certainly didn't run in a JavaScript VM.

There seems to have been a big spike in nostalgia around dial-up lately and I've seen several fantastic videos of people setting up their own homebrew dial-up networks. I can definitely see someone wanting to recreate an AIM server using period correct hardware. Implementing this in C, albiet targetting POSIX only systems at the moment, makes the possibility of that happening more likely.

## State of the Union:

Currently, only a portion of the authentication handshaking is happening.

## Building

A more complete build doc can be found here: [Build Documentation](docs/building.md).

TL;DR:

```c
mkdir build && cd build
cmake .. && make
```

## Disclaimers

Hopefully this goes without saying, but this shouldn't be used in any sort of production capacity. This is a fun project to recreate an old service. Any password entered is only hashed with the MD5 algorithm.

In the SQLite3 reference integration, input is not sanitized for any sort of SQL injection (you're more than welcome to improve it and submit a PR! 😊).

All traffic is unencrypted (again... PR if you want to bring in TLS 😊😊).

Also, it's written in C and if you really wanted to, you can export the ports it spins up to the broader internet. While I do run some static code analysis and valgrid, memory safety was not my top priority, so... attempt as much stacksmashing as your heart desires!

Also, sockets are handled with polling and all execution happens in a single thread, so efficiency is probably not all that great.
