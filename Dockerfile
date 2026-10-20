FROM debian:bookworm-slim AS build
RUN apt-get update && apt-get install -y --no-install-recommends g++ && rm -rf /var/lib/apt/lists/*
WORKDIR /src
COPY COMPSHOP.cpp webserver.cpp ./
RUN g++ -std=c++17 -O2 -Wall -Wextra -pedantic COMPSHOP.cpp -o /compshop && \
    g++ -std=c++17 -O2 -Wall -Wextra -pedantic webserver.cpp -o /computer-shop-server

FROM debian:bookworm-slim
COPY --from=build /computer-shop-server /usr/local/bin/computer-shop-server
EXPOSE 5000
USER 10001:10001
CMD ["/usr/local/bin/computer-shop-server"]
