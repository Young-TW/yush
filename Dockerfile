# Yush – Young's Shell

FROM ubuntu:rolling AS builder

WORKDIR /app

RUN \
    apt update && \
    apt install -y build-essential git cmake

RUN git clone https://github.com/Young-TW/yush.git .
RUN mkdir build && cd build && cmake .. && make

FROM ubuntu:rolling

COPY --from=builder /app/build/yush /usr/local/bin/yush
ENTRYPOINT [ "yush" ]