## Usage and Command Line Flags
This code allows a user to specify boundary conditions, the size of the grid, the number of iterations, the initial guess, and the subsequent file where the numerical solution is printed.  The following table specifies the command line flags which facilitates the input processing and their descriptions.

| Command Line Flag | Description |
| ------------- | ------------- |
| `-f`,`--file`  | The name of the file in which the numerical solution will be printed.  This flag is required.|
| `-g`,`--guess`  | The value for the initial guess of the solution. Its default vale is zero.|
| `-l`,`--left`  | The value of the boundary condition on the left side of the unit square or the y-axis. Its default vale is zero.|
| `-r`,`--right`  | The value of the boundary condition on the right side of the unit square or the line x=1.  Its default vale is zero.|
| `-t`,`--top`  | The value of the boundary condition on the top side of the unit square or the line y=1. Its default vale is zero.|
| `-b`,`--bottom`  | The value of the boundary condition on the bottom side of the unit square or the x-axis. Its default vale is zero.|
| `-s`,`--size`  | The number of bins on each axis of the grid discretizing the unit square.  For example, if the argument after this flag is `3` each axis is partitioned into `3` sections and there are `(3+1)*(3+1)=16` grid points as a result.  This flag is required.|
| `-i`,`--iterations`  | Number of iterations for the relaxation method.  This flag is required.|

## Ouput
The format of the ouput file after running this code is three columns with their respective values being the x-value, y-value, and solution (at the x-value and y-value).  This format allows the user to easily use gnuplot or a similar plotting software to visualize the solution. 

## Example
After running the following commands
```
$ bash build
$ ./relaxation -l 5 -s 100 -i 10000 -f out.txt -t 6
$ gnuplot
$ plot 'out.txt' with image
```
The following plot is produced

![image](/images/example1.png)
