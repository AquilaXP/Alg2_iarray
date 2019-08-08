Array
all milliseconds, count iteration = 100000

  |        Name | insertBegin |  insertRnd |  insertEnd |  readBegin  |   readRnd |    readEnd | removeBegin |  removeRnd |  removeEnd |
  |-------------|-------------|------------|------------|-------------|-----------|------------|-------------|------------|------------|
  | SingleArray |        1522 |       1579 |       2807 |          0  |         0 |          0 |        2752 |        474 |        430 |
  | VectorArray |         468 |        233 |          4 |          0  |         0 |          0 |         475 |        233 |          0 |
  | FactorArray |         466 |        229 |          0 |          0  |         0 |          0 |         463 |        232 |          0 |
  | MatrixArray |        1131 |        574 |          1 |          0  |         0 |          0 |        1003 |        501 |          2 |
  | LinkedArray |           3 |      22352 |          3 |          0  |      5112 |      10161 |           1 |       4139 |       5125 |
  |  SpaceArray |        1124 |      15221 |          1 |          0  |       223 |        446 |           3 |        445 |        446 |
  |     StlList |           3 |      22318 |          3 |          0  |      5151 |      10111 |           1 |       4081 |       5242 |
  
all microseconds, count iteration = 100000

  |        Name | insertBegin |  insertRnd |  insertEnd |  readBegin  |   readRnd |    readEnd | removeBegin |  removeRnd |  removeEnd |
  |-------------|-------------|------------|------------|-------------|-----------|------------|-------------|------------|------------|
  | SingleArray |     1574466 |    1604229 |    2968953 |        147  |       151 |        123 |     2868686 |     488324 |     426093 |
  | VectorArray |      464381 |     232800 |       4955 |        146  |       148 |        122 |      473663 |     231113 |        366 |
  | FactorArray |      462728 |     229871 |        402 |        146  |       146 |        122 |      458131 |     231292 |        367 |
  | MatrixArray |     1079336 |     543121 |       1245 |        698  |       899 |        943 |      995969 |     498907 |       2119 |
  | LinkedArray |        2876 |   22392424 |       3274 |        171  |   5102607 |   10053109 |        1825 |    4070924 |    5184380 |
  |  SpaceArray |     1117431 |   15181720 |       1704 |        351  |    224070 |     445634 |        3122 |     445197 |     448074 |
  |     StlList |        3081 |   22293274 |       2993 |        177  |   5158587 |   10103562 |        1801 |    4089977 |    5260829 |
