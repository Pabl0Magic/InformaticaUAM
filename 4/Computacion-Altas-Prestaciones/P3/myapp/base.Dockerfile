FROM ubuntu:22.04

RUN apt-get update \
 && apt-get install -y openjdk-11-jre \
 && apt-get -y install curl \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

# HADOOP
ENV HADOOP_VERSION 3.3.1
ENV SPARK_VERSION 3.3.1

RUN mkdir -p /opt && cd /opt && curl "http://archive.apache.org/dist/hadoop/common/hadoop-${HADOOP_VERSION}/hadoop-${HADOOP_VERSION}.tar.gz" \
  | tar -zx hadoop-${HADOOP_VERSION}/lib/native \
 && ln -s hadoop-${HADOOP_VERSION} hadoop

# SPARK
RUN mkdir -p /opt && cd /opt && \ 
  curl "https://archive.apache.org/dist/spark/spark-${SPARK_VERSION}/spark-${SPARK_VERSION}-bin-hadoop3.tgz" \
  |  tar -zx\
 && ln -s spark-${SPARK_VERSION}-bin-hadoop3 spark
 
ENV PATH $PATH:/opt/spark/bin