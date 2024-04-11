# run: docker build -t exercise .           # - jednokrotnie
# then run: docker run --rm exercise        # potem po kazdych zmianach
# cleanup after test: docker rmi exercise   # po zakonczeniu zadania (czyszczenie obrazu dockera)

FROM ubuntu:21.04

MAINTAINER Grzegorz Prowadzacy

#### instalacja zaleznosci:
RUN apt-get update
# RUN apt-get upgrade -y
RUN apt-get install --no-install-recommends -y git cmake apt-utils build-essential libgtest-dev


#### Przygotowanie plikow
RUN mkdir -p /home/exercise/exercise_build/
ADD . /home/exercise/

WORKDIR /home/exercise/exercise_build/

#### cmake generuje co trzeba
RUN cmake ..
RUN make -j4 tests

# wystawienie komendy na zewnatrz:
CMD make run_tests
