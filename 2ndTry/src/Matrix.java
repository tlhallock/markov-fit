
public class Matrix implements Expression {

	public final int m;
	public final int n;
	
	Expression[][] elems;

	public Matrix(int m, int n) {
		this.m = m;
		this.n = n;
		elems = new Expression[m][n];
	}

	@Override
	public StringBuilder toC(StringBuilder builder) {
		throw new RuntimeException("Should not have to print this.");
	}

	@Override
	public Expression clone() {
		return null;
	}

	@Override
	public Expression simplify() {
		if (m == 1 && n == 1)
		{
			return Expression.simplifyExpression(elems[0][0]);
		}
		
		for (int i=0;i<m;i++)
		{
			for(int j=0;j<n;j++)
			{
				elems[i][j] = Expression.simplifyExpression(elems[i][j]);
			}
		}
		
		return this;
	}
	
	public void multiply(Value value)
	{
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				elems[i][j] = new Product(value, elems[i][j]);
			}
		}
	}
	
	
	
	public static Matrix createMatrix(String varName, int m, int n) {
		Matrix matrix = new Matrix(m, n);

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				matrix.elems[i][j] =
						new Variable(varName + "[" + (i * m + j) + "]");
//						new Variable(varName + "[" + i + "," + j + "]");
//						new Variable(varName + "[" + m + "*" + i + "+" + j + "]");
			}
		}

		return matrix;
	}

	public static Matrix multiply(Matrix mat1, Matrix mat2) {
		int m = mat1.m;
		int n = mat2.n;
		int k = mat1.n;

		if (k != mat2.m) {
			throw new RuntimeException("Matrix dimensions: " + mat1.m + ", " + mat1.n + ", " + mat2.m + ", " + mat2.n);
		}

		Matrix returnValue = new Matrix(m, n);

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				Sum sum = new Sum();
				for (int l = 0; l < k; l++) {
					sum.add(new Product(mat1.elems[i][l], mat2.elems[l][j]));
				}
				returnValue.elems[i][j] = sum;
			}
		}

		return returnValue;
	}
	
	public static Matrix createZeros(int m, int n)
	{
		Matrix returnValue = new Matrix(m, n);

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				returnValue.elems[i][j] = new Zero();
			}
		}
		
		return returnValue;
	}
	
	public static Matrix createOnes(int m, int n)
	{
		Matrix returnValue = new Matrix(m, n);

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				returnValue.elems[i][j] = new One();
			}
		}
		
		return returnValue;
	}
	
	public static Matrix createIdentity(int order)
	{
		Matrix returnValue = new Matrix(order, order);
		
		for (int i = 0; i < order; i++) {
			for (int j = 0; j < order; j++) {
				returnValue.elems[i][j] = i == j ? new One() : new Zero();
			}
		}
		
		return returnValue;
	}

	@Override
	public Expression differentiate(Variable variable) {
		throw new RuntimeException("Should not have to print this.");
	}
}
