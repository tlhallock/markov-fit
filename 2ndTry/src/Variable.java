
public class Variable implements Expression {

	public String name;
	
	public Variable(String name)
	{
		this.name = name;
	}
	
	
	public boolean equals(Object other)
	{
		if (!(other instanceof Variable))
		{
			return false;
		}
		
		Variable var = (Variable) other;
		return name.equals(var.name);
	}


	@Override
	public StringBuilder toC(StringBuilder builder) {
		return builder.append(name);
	}

	@Override
	public Expression clone() {
		return new Variable(name);
	}


	@Override
	public Expression simplify() {
		return this;
	}


	@Override
	public Expression differentiate(Variable variable) {
		if (equals(variable))
		{
			return new One();
		}
		return new Zero();
	}
}
