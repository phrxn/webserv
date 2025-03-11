FROM alpine:3.21.3

#sources files
COPY ./src /src/src
COPY Makefile /src/Makefile
COPY build.sh /src/build.sh

# app folder
COPY ./conf /app/conf
COPY ./www_tests/17_cgi_fake_box /app/www_tests/17_cgi_fake_box/

RUN apk update \
    && apk add --no-cache \
	php \
	php-cgi \
	php-session \
	clang \
	make \
	bash \
	&& \
	ln -sf /usr/bin/clang++ /usr/bin/c++ \
	&& \
	ln -sf /usr/bin/php-cgi /bin/php-cgi \
	&& \
	chmod +x /src/build.sh \
	&& \
	cd /src \
	&& \
	bash ./build.sh compile \
	&& \
	mkdir -p /app  /app/tmp \
	&& \
	cp webserv /app/webserv \
	&& \
	rm -rf /src

WORKDIR /app

EXPOSE 9000

CMD [ "./webserv", "www_tests/17_cgi_fake_box/config.conf" ]