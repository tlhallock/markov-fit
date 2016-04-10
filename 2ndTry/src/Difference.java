public class Difference implements Expression
{
	Expression left;
	Expression right;

	Difference(Expression left, Expression right)
	{
		this.left = left;
		this.right = right;
	}
	
	@Override
	public StringBuilder toC(StringBuilder builder) {
		return right.toC(left.toC(builder.append("(")).append("-(")).append(")");
	}
	

	public Expression clone()
	{
		return new Difference(left.clone(),  right.clone());
	}

	@Override
	public Expression simplify() {
		left = Expression.simplifyExpression(left);
		right = Expression.simplifyExpression(right);
		if (left instanceof Zero)
		{
			return right;
		}
		if (right instanceof Zero)
		{
			return left;
		}
		return this;
	}

	@Override
	public Expression differentiate(Variable variable) {
		return new Difference(left.differentiate(variable), right.differentiate(variable));
	}
}
