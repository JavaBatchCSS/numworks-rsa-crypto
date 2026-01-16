APP_NAME = rsa_crypto
OUTPUT_DIR = output

SOURCES = $(addprefix src/,\
  app.cpp \
  controller.cpp \
)

include ../build/external_app.mak
