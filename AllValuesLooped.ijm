rnum = "100_1"
binning = 4;
bin = 0;

if (binning == 1) {
	bin = 512;
	bin = 512-8; //to exclude edge events; needs to be consistent with each type of binning
}
else if (binning == 2) {
	bin = 256;
	bin = 256-4; //to exclude edge events; needs to be consistent with each type of binning
}
else if (binning == 4) {
	bin = 128;
	bin = 128-2; //to exclude edge events; needs to be consistent with each type of binning
}

prefix = "/media/gwendolyn/SLIMER\ DATA/Run";
ext = ".tif";
total = prefix + rnum + "/Pos0/";
subtotal = prefix + rnum + "/";

m=5000;
n=9999;

setBatchMode(true);

for(x = m; x<=n; x++){
	if(x<10){filename = "img_00000000";}
	else if(x<100){filename = "img_0000000";}
	else if(x<1000){filename = "img_000000";}
	else if(x<10000){filename = "img_00000";}
	else {filename = "img_0000";}
	open(subtotal + "blur/" + filename + x + "smooth" + ext);
	
	count = 0;
	events = false;
	
	for (j = 2; j < bin; j++) {
		for (i = 2; i < bin; i++) {
			val = getPixel(i,j);
			if (val > 90) {
				//print(i," ",j," ",val);
				examineArea(i-10,i+10,j-10,j+10);
				if (count >= 20) {
					events = true;
				}
			}
		}
	}
	if (events == false) {
		//print("sorry, no events");
		saveAs(subtotal + "blur/noevents/" + filename + x + "not" + ext);
	}
	else {
		//print("congrats, you found an event!");
		saveAs(subtotal + "blur/events/" + filename + x + "event" + ext);
	}
}

function examineArea(a,b,c,d) {
	for (j = c; j < d; j++) {
		for (i = a; i < b; i++) {
			val = getPixel(i,j);
			if (val > 65) {
				count++;
			}
		}
	}
//print(count);
}

close();
setBatchMode(false);
