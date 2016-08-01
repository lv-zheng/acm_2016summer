
while true; do
	python hfuck.py > hf.in
	./Hac < hf.in > hac.out
	./H < hf.in > hwa.out
	if ! diff hac.out hwa.out; then
		echo WA
		exit
	else
		echo AC
	fi
done
