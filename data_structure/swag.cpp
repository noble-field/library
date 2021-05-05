//-------------------------------------------------
//--Sliding Windows Aggregation
//-------------------------------------------------
template<class T, T(*op)(T,T)>
class SWAG
{	
private:
	struct Item {T val,cum;};
	stack<Item> f_stack, b_stack;
public:
	SWAG(){}
	T calc(){
		if (f_stack.empty()){
			return b_stack.top().cum;
		}else if(b_stack.empty()){
			return f_stack.top().cum;
		}
		return op(f_stack.top().cum, b_stack.top().cum);
	}
	void push(T x){
		if (b_stack.empty()){
			b_stack.push(Item{x,x});	
		}else{
			b_stack.push(Item{x,op(b_stack.top().cum,x)});
		}
	}
	void pop(){
		if (f_stack.empty()){
			{
				Item item = b_stack.top(); b_stack.pop();
				f_stack.push(Item{item.val,item.val});
			}
			while(!b_stack.empty()){
				Item item = b_stack.top(); b_stack.pop();
				f_stack.push(Item{item.val,op(item.val,f_stack.top().cum)});
			}
		}
		f_stack.pop();
	}
};
