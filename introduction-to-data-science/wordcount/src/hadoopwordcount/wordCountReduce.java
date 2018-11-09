package hadoopwordcount;

import java.io.IOException;


import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class wordCountReduce extends Reducer<Text, Text, Text, Text> {
	@Override
	//key is word values is {1,1...}
	protected void reduce(Text key, Iterable<Text> values,Context context) throws IOException, InterruptedException {
		String result="";
		for(Text num:values){
			result+=num.toString()+'|';
		}
		context.write(key, new Text(result));//因为数据类型不同，因此需要new
	}
 
}
