import java.util.Iterator;
import java.util.LinkedList;

public class Product implements Expression {

	LinkedList<Expression> factors = new LinkedList<>();

	public Product() {

	}

	public Product(Expression left, Expression right) {
		factors.add(left);
		factors.add(right);
	}

	void multiply(Expression expr) {
		factors.add(expr);
	}

	@Override
	public StringBuilder toC(StringBuilder builder) {
		Iterator<Expression> iterator = factors.iterator();

		iterator.next().toC(builder.append("(")).append(")");
		while (iterator.hasNext())
			iterator.next().toC(builder.append("*(")).append(")");

		return builder;
	}

	public Expression clone() {
		Product sum = new Product();
		for (Expression term : factors) {
			sum.multiply(term.clone());
		}
		return sum;
	}

	@Override
	public Expression simplify() {
		
		
		double p = 1.0;

		LinkedList<Expression> newFactors = new LinkedList<>();
		for (Expression expr : factors) {
			Expression e = Expression.simplifyExpression(expr);

			if (e instanceof Zero) {
				return new Zero();
			}
			if (e instanceof One) {
				continue;
			}
			if (e instanceof Product)
			{
				newFactors.addAll(((Product) e).factors);
				continue;
			}
			if (e instanceof Value)
			{
				p *= ((Value) e).getValue();
				continue;
			}

			newFactors.add(e);
		}
		
		if (p != 1.0)
		{
			newFactors.addFirst(new Value(p));
		}

		if (newFactors.size() == 0) {
			return new One();
		}

		if (newFactors.size() == 1) {
			return newFactors.get(0);
		}

		factors = newFactors;
		return this;

		// factors.removeIf((Expression e) -> e instanceof One);
	}

	@Override
	public Expression differentiate(Variable variable) {

		int size = factors.size();

		Sum sum = new Sum();

		for (int i = 0; i < size; i++) {
			Product product = new Product();

			int count = 0;
			for (Expression expr : factors) {
				if (count++ == i) {
					product.multiply(expr.differentiate(variable));
				} else {
					product.multiply(expr.clone());
				}
			}

			sum.add(product);
		}

		return sum;
	}
}
