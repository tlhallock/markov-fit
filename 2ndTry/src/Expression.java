
public interface Expression {
	
	StringBuilder toC(StringBuilder builder);
	Expression clone();
	
	Expression simplify();
	
	Expression differentiate(Variable variable);
	
	
	
	public static Expression simplifyExpression(Expression e)
	{
//		while (true)
//		{
//			Expression next = e.simplify();
//			
//			if (next == e)
//			{
//				break;
//			}
//			
//			e = next;
//		}
//		// Do it twice for some reason...
		while (true)
		{
			Expression next = e.simplify();
			
			if (next == e)
			{
				return e;
			}
			
			e = next;
		}
	}
}
