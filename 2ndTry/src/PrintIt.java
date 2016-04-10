import java.io.File;
import java.io.PrintStream;


public class PrintIt {

	static Expression getMatrixExponential(Matrix left, Matrix matrix, Matrix right, int order) {
		Sum sum = new Sum();

		Matrix currentPower = Matrix.createIdentity(matrix.m);
		double denominator = 1.0;

		for (int i = 0; i <= order; i++)
		{
			if (i > 0)
				denominator /= i;
			
			sum.add(new Product(new Value(denominator),
							Expression.simplifyExpression(
									Matrix.multiply(
											Matrix.multiply(left, currentPower),
											right))));

			currentPower = Matrix.multiply(matrix, currentPower);
		}

		return Expression.simplifyExpression(sum);
	}
	
	
	
	
	
	
	
	
	
	

	public static void main(String[] args) throws Exception {
		int n = 3;
		int order = 5;

		Matrix left = Matrix.createZeros(1, n);
		left.elems[0][n - 1] = new One();
		Matrix right = Matrix.createOnes(n, 1);
		Matrix middle = Matrix.createMatrix("q", n, n);

		Expression expr = getMatrixExponential(left, middle, right, order);

		PrintStream ps = new PrintStream(new File ("generated.cpp"));

		String signature = "double mat_exp_" + n + "_" + order + "(const double *const q)"; 
		System.out.println(signature);
		
		ps.println(signature + " {");
		ps.print("\treturn ");
		ps.print(expr.toC(new StringBuilder()).toString());
		ps.print(";\n");
		ps.println("}");
		

		ps.println("void mat_exp_grad(const double *const q, double *output) {");
		for (int i=0;i<n*n;i++)
		{
			ps.print("\toutput[" + i + "] = -(");
			ps.print(Expression.simplifyExpression(expr.differentiate(new Variable("q[" + i + "]"))).toC(new StringBuilder()));
			ps.println(");");
		}
		ps.println("}");
	}

}
