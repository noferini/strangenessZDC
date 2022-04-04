#!/bin/bash
root -b -q -l mctruthSD.C\($1\);
root -b -q -l mctruthSPD_SD.C\($1\);
root -b -q -l mctruth.C\($1\);
root -b -q -l mctruthSPD.C\($1\);
