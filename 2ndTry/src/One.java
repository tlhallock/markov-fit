
public class One implements Expression {

	@Override
	public StringBuilder toC(StringBuilder builder) {
		return builder.append("1");
	}

	@Override
	public Expression clone() {
		return new One();
	}

	@Override
	public Expression simplify() {
		return this;
	}

	@Override
	public Expression differentiate(Variable variable) {
		return new Zero();
	}

}
