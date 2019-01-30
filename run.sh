#!/bin/bash

DIR="runs"


NAME="prey_predator"
NGRID=50
NPRED=20
NPREY=500
PREY_SP=300
PRED_SPAWN_RATE=50;
PRED_DEATH_RATE=20;
PREY_SPAWN_RATE=70;
PREY_DEATH_RATE=10;
mkdir "$DIR/$NAME"
LOGFILE="$DIR/$NAME/$NAME-$NGRID-$NPREY-$NPRED-$PRED_SPAWN_RATE-$PRED_DEATH_RATE-$PREY_SPAWN_RATE-$PREY_DEATH_RATE.txt"
MOVIEFILE="$DIR/$NAME/$NAME-$NGRID-$NPREY-$NPRED-$PRED_SPAWN_RATE-$PRED_DEATH_RATE-$PREY_SPAWN_RATE-$PREY_DEATH_RATE.mvi"
echo "" > $LOGFILE
echo -e "\n\n$NAME\n" >> $LOGFILE
./predator_prey/a.out $MOVIEFILE $NGRID $NPREY $NPRED $PRED_SPAWN_RATE $PRED_DEATH_RATE $PREY_SPAWN_RATE $PREY_DEATH_RATE >> $LOGFILE
./softplot/a.out $MOVIEFILE
python3 plotter.py $LOGFILE


# NAME="lane_formation"
# # NAME="lane_formation_verlet"
# # NAME="pinning_sites"
# mkdir "$DIR/$NAME"
# LOGFILE="$DIR/$NAME.txt"
# echo "" > $LOGFILE
# for N in 50 100 200 300 400 500
# do
#     MOVIEFILE="$DIR/$NAME/$NAME-$N.mvi"
#     echo $MOVIEFILE
#     echo -e "\n\n$NAME-$N\n" >> $LOGFILE
#     ./molec_dyn/a.out $N $MOVIEFILE >> $LOGFILE
# done


# NAME="ising"
# mkdir "$DIR/$NAME"
# LOGFILE="$DIR/$NAME.txt"
# gcc mc_ising.c -lm
# echo "" > $LOGFILE
# for N in 10 15 20 30 40
# do
#     MOVIEFILE="$DIR/$NAME/$NAME-$N.mvi"
#     echo $MOVIEFILE
#     echo -e "\n\n$NAME-$N\n" >> $LOGFILE
#     ./a.out $N $MOVIEFILE >> $LOGFILE
# done


# NAME="dla_fractal"
# mkdir "$DIR/$NAME"
# LOGFILE="$DIR/$NAME.txt"
# gcc "$NAME.c" -lm
# echo "" > $LOGFILE
# N=150
# for P in 10 35 50 75 90
# do
#     MOVIEFILE="$DIR/$NAME/$NAME-$N-$P.mvi"
#     echo $MOVIEFILE
#     echo -e "\n\n$NAME-$N-$P\n" >> $LOGFILE
#     ./a.out $P $N $MOVIEFILE >> $LOGFILE
# done

# NAME="percolation"
# mkdir "$DIR/$NAME"
# LOGFILE="$DIR/$NAME.txt"
# gcc "$NAME.c" -lm
# echo "" > $LOGFILE
# N=150
# for P in 10 35 50 75 90
# do
#     MOVIEFILE="$DIR/$NAME/$NAME-$N-$P.mvi"
#     echo $MOVIEFILE
#     echo -e "\n\n$NAME-$N-$P\n" >> $LOGFILE
#     ./a.out $P $N $MOVIEFILE >> $LOGFILE
# done


# NAME="network"
# mkdir "$DIR/$NAME"
# gcc "$NAME.c" -lm
# N=100
# for L in 200 500 2000 4000
# do
#     LOGFILE="$DIR/$NAME/$NAME-n$N-l$L.txt"
#     ./a.out $N $L >> $LOGFILE
#     python3 plotter.py $LOGFILE
#     LOGFILE="$DIR/$NAME/$NAME-rand-n$N-l$L.txt"
#     ./a.out $N $L $L >> $LOGFILE
#     python3 plotter.py $LOGFILE
# done


