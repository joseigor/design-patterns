FROM ghcr.io/joseigor/zenv:latest 

LABEL maintainer="joseigorcfm@gmail.com"

ARG WORKDIR_PATH
WORKDIR ${WORKDIR_PATH}
