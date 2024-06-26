# WebDC

WebRTC datachannel library and server.

The library implements a minimal subset of WebRTC to achieve unreliable and out of order UDP transfer for browser clients.
See the [EchoServer](https://github.com/ayamir/webdc/blob/master/examples/EchoServer.c) for how to connect to the server from a browser.
The core library (Dc) is platform independent. Refer to `HostEpoll` for linux-platform usage.

## Example

The `EchoServer` should listen the public IP directly.

![image-20240227110417430](https://raw.githubusercontent.com/ayamir/blog-imgs/main/image-20240227110417430.png)

![image-20240221215854419](https://raw.githubusercontent.com/ayamir/blog-imgs/main/image-20240221215854419.png)

## Developing

```bash
bash ./generate_clangd.sh # generate .clangd file for clangd-based editor
```

## Building

Build passed on `Ubuntu18.04` with `openssl` `1.1.1`.

```bash
mkdir build && cd build
cmake ..
make -j
```

## Todo

- [x] user data fragmentation
- [x] ordered transmission
- [ ] reliable transmission
- [ ] multi-stream multiplexing
