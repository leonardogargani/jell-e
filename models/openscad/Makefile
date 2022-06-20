%.stl: %.scad
	openscad $< -o $@

%.png: %.scad
	openscad --autocenter --viewall --imgsize=10000,10000 --colorscheme DeepOcean $< -o $@
	convert $@ -resize 10% $@

clean:
	rm -f *.stl *.png

