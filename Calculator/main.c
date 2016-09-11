//
//  main.c
//  Calculator
//
//  Created by Edoardo Franco Vianelli on 9/10/16.
//  Copyright © 2016 Edoardo Franco Vianelli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double round_double(double n){
    
    uint64_t sans_trail = (uint64_t)n;
    double trail = n - sans_trail;
    if (trail < 0.5){
        return sans_trail;
    }
    
    return sans_trail + 1.0;
}

double square_root(double n){
    
    if (n < 0) n *= -1;
    
    //find upper root and lower root
    
    double rounded        = round_double(n);
    
    double squares[10]    = {1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
    double upper_base     = 9;
    double current_square = squares[(int)upper_base++];
    uint8_t iterated      = 0;
    
    while (rounded > current_square){
        upper_base++;
        current_square    = upper_base * upper_base;
        iterated          = 1;
    }
    
    if (iterated == 0){
        int i;
        for (i = 9; i >= 0; i--){
            upper_base      = (double)i;
            
            if (squares[(int)upper_base] < rounded){
                upper_base += 2;
                break;
            }else if (squares[(int)upper_base] == rounded){
                upper_base += 1;
                break;
            }
        }
    }
    
    current_square      = upper_base * upper_base;
    
    double   lower_base = upper_base - 1;
    double lower_square = lower_base * lower_base;
    
    double difference   = current_square - lower_square;
    double n_lower_diff = n - lower_square;
    
    double res          = (lower_base + (n_lower_diff / difference));
    
    if (res != round_double(res)){
        double ratio    = (res * res) / n;
        double diff     = 1 - ratio;
        return res * (1 + diff/2);
    }
    
    return res;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    char s[64];
    
    while (strcmp(s, "q") != 0){
        
        printf("Enter a value to find the square root of: ");
        scanf("%s", s);
        double num  = atof(s);
        double root = square_root(num);
        printf("The square root of %.2f is %.2f\n", num, root);
        double found_num = root*root;
        printf("%f^2 = %f with an precision of %f percent\n\n", root, found_num, 100*found_num/num);
    }
    
    return 0;
}
