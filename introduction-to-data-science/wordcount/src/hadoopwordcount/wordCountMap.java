package hadoopwordcount;

import java.io.IOException;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;


public class wordCountMap extends Mapper<LongWritable, Text, Text, Text>
{
	@Override
	protected void map(LongWritable key, Text value, Context context)
			throws IOException, InterruptedException {
		// TODO Auto-generated method stub
		String[] lines=value.toString().split(" ");//string中储存每一个单词
		for (String word : lines) {
			boolean result = word.matches("[\\u4e00-\\u9fa5]+"); //判断是否是中文
			if(word.length()>1 && result==true){
			  context.write(new Text(word), new Text(lines[0].substring(0, lines[0].length()-4)));}
		}
	}
}
