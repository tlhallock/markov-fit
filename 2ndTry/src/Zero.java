
public class Zero implements Expression {

	@Override
	public StringBuilder toC(StringBuilder builder) {
		return builder.append("0");
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
