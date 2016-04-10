import java.util.Iterator;
import java.util.LinkedList;

public class Sum implements Expression {

	LinkedList<Expression> terms = new LinkedList<>();

	
	void add(Expression expr)
	{
		terms.add(expr);
	}
	
	
	@Override
	public StringBuilder toC(StringBuilder builder) {
		Iterator<Expression> iterator = terms.iterator();

		iterator.next().toC(builder.append("(")).append(")");
		
		while (iterator.hasNext())
			iterator.next().toC(builder.append("+(")).append(")");
		
		return builder;
	}

	public Expression clone()
	{
		Sum sum = new Sum();
		for (Expression term : terms)
		{
			sum.add(term.clone());
		}
		return sum;
	}

	@Override
	public Expression simplify() {
		
		double s = 0;
		
		LinkedList<Expression> newTerms = new LinkedList<>();
		for (Expression expr : terms)
		{
			Expression e = Expression.simplifyExpression(expr);
			
			if (e instanceof Zero)
			{
				continue;
			}
			
			if (e instanceof Sum)
			{
				newTerms.addAll(((Sum) e).terms);
				continue;
			}
			
			if (e instanceof One)
			{
				s += 1;
				continue;
			}
			
			if (e instanceof Value)
			{
				s += ((Value) e).getValue();
				continue;
			}
			
			newTerms.add(e);
		}
		
		if (s != 0)
		{
			if (s == 1)
			{
				newTerms.addFirst(new One());
			}
			else
			{
				newTerms.addFirst(new Value(s));
			}
		}
		
		if (newTerms.size() == 0)
		{
			return new Zero();
		}
		
		if (newTerms.size() == 1)
		{
			return newTerms.get(0);
		}
		
		terms = newTerms;
		return this;
		
//		factors.removeIf((Expression e) -> e instanceof One);
	}


	@Override
	public Expression differentiate(Variable variable) {
		Sum sum = new Sum();
		
		for (Expression term : terms)
		{
			sum.terms.add(term.differentiate(variable));
		}
		
		return sum;
	}
}
