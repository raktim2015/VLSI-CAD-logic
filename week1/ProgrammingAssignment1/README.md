Complement of a boolean function using URP

Idea : 
We can represent a boolean expression using Shanon cofactor:
F(x,y,z) = x.F(x==1) + x'.F(x==0)
If we take the complement
F(x,y,z)' = (x.F(x==1) + x'.F(x==0))'
....
F(x,y,z)' = x.(F(x==1))' + x'.(F(x==0))'

We can recursively compute the result for every variable and return the output

func Complement()
{

    // base conditions goes here
    {
        ...
    }
    let x = find the variable x after getting the most binate
    let P = Complement(Positive cofactor of F wrt x)
    let N = Complement(Negative cofactor of F wrt x)
    let var1 = AND(x,P)
    let var2 = AND(x',N)
    let res = OR(var1, var2)
    return res
}
