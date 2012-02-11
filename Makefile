
all: Front Back

Front: src/front/main.cpp src/front/interactive-stream-handler.cpp src/front/interactive-stream-handler.h src/front/transaction-file-writer.cpp src/front/transaction-file-writer.h src/front/bank-account-reader.h src/front/bank-account-reader.cpp
	g++ -o bin/Front.exe src/front/main.cpp src/front/interactive-stream-handler.h src/front/interactive-stream-handler.cpp src/front/transaction-file-writer.cpp src/front/transaction-file-writer.h src/front/bank-account-reader.h src/front/bank-account-reader.cpp

Back: src/back/BackEnd.h src/back/BackEnd.cpp src/back/main.cpp
	g++ -o bin/Back.exe src/back/BackEnd.h src/back/BackEnd.cpp src/back/main.cpp

Java:FrontEnd.class

#FrontEnd.jar : FrontEnd.class
#	jar cfvm bin/FrontEnd.jar bin/manifest.txt src/front-java/*.java bin/*.class
#	rm bin/*.class

FrontEnd.class : src/front-java/FrontEnd.java Bank.class CBAReader.class Messages.class 
	javac -d bin -cp bin/ src/front-java/FrontEnd.java
	
Account.class : src/front-java/Account.java
	javac -d bin src/front-java/Account.java
	
Bank.class : src/front-java/Bank.java Account.class Messages.class TransactionWriter.class
	javac -d bin -cp bin/ src/front-java/Bank.java
	
CBAReader.class : src/front-java/CBAReader.java Account.class
	javac -d bin -cp bin/ src/front-java/CBAReader.java
	
Messages.class : src/front-java/Messages.java
	javac -d bin src/front-java/Messages.java
	
TransactionWriter.class : src/front-java/TransactionWriter.java
	javac -d bin src/front-java/TransactionWriter.java
	
clean:
	#cleaning
	rm bin/*.exe
	rm bin/*.class
