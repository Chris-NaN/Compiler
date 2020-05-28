file=$(ls test/)
for f in $file
do
	./minipascal test/$f > output_dir/$f
done
