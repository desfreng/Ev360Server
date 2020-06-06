FROM ev3cc

RUN export DEBIAN_FRONTEND=noninteractive && \
    sudo apt-get update && \
    sudo apt-get upgrade --yes --no-install-recommends

RUN DEBIAN_FRONTEND=noninteractive sudo apt-get install --yes --no-install-recommends \
         gdbserver
