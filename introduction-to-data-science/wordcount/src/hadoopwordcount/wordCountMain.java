package hadoopwordcount;

import java.net.URI;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;


//import org.apache.log4j.chainsaw.Main;

public class wordCountMain {
	public static void main(String[] args) throws Exception
    {
		String inputPath="hdfs://192.168.191.139:9000/input";
		String outputPath="hdfs://192.168.191.139:9000/output";
		
		Configuration conf =new Configuration();
		
		//判断输出路径是否存在，存在则删除
		FileSystem fileSystem =FileSystem.get(new URI(inputPath),conf);
		if(fileSystem.exists(new Path(outputPath))){
			fileSystem.delete(new Path(outputPath),true);
		}
			
		Job job =new Job(conf,"wordCount");
		
		FileInputFormat.setInputPaths(job,inputPath);//设置输入路径
		FileOutputFormat.setOutputPath(job, new Path((outputPath)));
		
		//配置job
		job.setJarByClass(wordCountMain.class); // 标明class入口
		job.setMapperClass(wordCountMap.class);
		job.setReducerClass(wordCountReduce.class);
		
		//代码输出信息
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);
		job.waitForCompletion(true);
	}
}
