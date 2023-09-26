spark = SparkSession.builder.appName(APP_NAME).master(SPARK_URL)\
    .config("spark.driver.host",IP).gerOrCreate()