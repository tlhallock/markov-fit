
public class Value implements Expression {

	double value;
	
	public Value(double value)
	{
		this.value = value;
	}
	
	@Override
	public StringBuilder toC(StringBuilder builder) {
		return builder.append(value);
	}

	@Override
	public Expression clone() {
		return new Value(value);
	}

	@Override
	public Expression simplify() {
		if (value == 0)
		{
			return new Zero();
		}
		if (value == 1)
		{
			return new One();
		}
		return this;
	}

	@Override
	public Expression differentiate(Variable variable) {
		return new Zero();
	}

	public double getValue() {
		return value;
	}
}
