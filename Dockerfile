FROM rust:latest AS builder

WORKDIR /app

COPY Cargo.toml Cargo.lock ./

RUN cargo fetch

COPY . .

RUN cargo build --release

FROM ubuntu:rolling

RUN apt-get update && apt-get install -y libssl-dev
COPY --from=builder /app/target/release/yush /usr/local/bin/yush
ENTRYPOINT [ "yush" ]
