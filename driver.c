# include<stdio.h>
# include"Symbol_Table.h"

int main() {
    begin 
        assign(INT, "a", "1");
        assign(STRING , "b", "Samuel");
        begin
            assign(STRING, "a", "Ravindra");
            assign(FLOAT, "c", "4.67");
            print("b");
            begin
                assign(INT, "c", "5");
                print("b");
                print("a");
                print("c");
            end
            print("a");
            print("c");
        end
        print("a");
    end
}
