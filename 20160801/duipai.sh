while true; do
	python fuck.py > fuck.in
	< fuck.in ./ma > ma.out
	< fuck.in ./ac > ac.out

	if ! diff ma.out ac.out ; then
		echo "WA"
		exit
	else
		echo "AC"
	fi
done
