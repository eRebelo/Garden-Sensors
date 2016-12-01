/*############################################################################################
ULTIMA LEITURA
############################################################################################*/

date = new Date(datasources["Garden"]["updateTime"]);

return "<h2 style=\"margin-left: 10px;\">Última leitura</h2></br><h3><center>" +  date.getDate() + "/" + date.getMonth() + "/" + date.getFullYear() + " " + date.getHours() + ":" + date.getMinutes() + ":" + date.getSeconds() + "</center></h3>";

/*############################################################################################
DATA MENOR TEMPERATURA
############################################################################################*/

tempMenor=100;

for (i=0; i< 50; i++) {
    dataTemp = datasources["Garden-All"][i]["content"]["temperature"];
    
	if ((tempMenor > dataTemp) && (dataTemp != "nan")) {
		tempMenor = dataTemp;
        timeStamp = datasources["Garden-All"][i]["updateTime"];
    }
}
date = new Date(timeStamp);
return "<h2 style=\"margin-left: 10px;\">Valores em função da MENOR temperatura registrada nas últimas 24 horas: </h2></br><h3><center>" + date.getDate() + "/" + date.getMonth() + "/" + date.getFullYear() + "\t" + date.getHours() + ":" + date.getMinutes() + ":" + date.getSeconds() + "</center></h3>";


/*############################################################################################
TEMP MENOR
############################################################################################*/

tempMenor=100;

for (i=0; i< 50; i++) {
    dataTemp = datasources["Garden-All"][i]["content"]["temperature"];
        
	if ((tempMenor > dataTemp) && (dataTemp != "nan")) {
        tempMenor = dataTemp;
    }
}

return tempMenor;

/*############################################################################################
UMIDADE NA TEMP MENOR
############################################################################################*/

tempMenor=100;

for (i=0; i< 50; i++) {
    dataTemp = datasources["Garden-All"][i]["content"]["temperature"];
        
	if ((tempMenor > dataTemp) && (dataTemp != "nan")) {
		tempMenor = dataTemp;
		humidity = datasources["Garden-All"][i]["content"]["humidity"];
    }
}

return humidity;

/*############################################################################################
UMIDADE DO SOLO NA TEMP MENOR
############################################################################################*/

tempMenor=100;

for (i=0; i< 50; i++) {
    dataTemp = datasources["Garden-All"][i]["content"]["temperature"];
        
	if ((tempMenor > dataTemp) && (dataTemp != "nan")) {
		tempMenor = dataTemp;
		hygrometer = datasources["Garden-All"][i]["content"]["hygrometer_value"];
    }
}

return hygrometer;

/*############################################################################################
DATA MAIOR TEMPERATURA
############################################################################################*/

tempMaior=0;

for (i=0; i< 50; i++) {
    dataTemp = datasources["Garden-All"][i]["content"]["temperature"];
    
	if ((tempMaior < dataTemp) && (dataTemp != "nan")) {
        tempMaior = dataTemp;
        timeStamp = datasources["Garden-All"][i]["updateTime"];
    }
}

date = new Date(timeStamp);
return "<h2 style=\"margin-left: 10px;\">Valores em função da MAIOR temperatura registrada nas últimas 24 horas: </h2></br><h3><center>" + date.getDate() + "/" + date.getMonth() + "/" + date.getFullYear() + "\t" + date.getHours() + ":" + date.getMinutes() + ":" + date.getSeconds() + "</center></h3>";

/*############################################################################################
TEMP MAIOR
############################################################################################*/

tempMaior=0;

for (i=0; i<50; i++) {
    dataTemp = datasources["Garden-All"][i]["content"]["temperature"];
	if ((tempMaior < dataTemp) && (dataTemp != "nan")) {
		tempMaior = dataTemp;
    }
}

return tempMaior;

/*############################################################################################
UMIDADE NA TEMP MAIOR
############################################################################################*/

tempMaior=0;

for (i=0; i< 50; i++) {
    dataTemp = datasources["Garden-All"][i]["content"]["temperature"];
        
	if ((tempMaior < dataTemp) && (dataTemp != "nan")) {
		tempMaior = dataTemp;
		humidity = datasources["Garden-All"][i]["content"]["humidity"];
    }
}

return humidity;

/*############################################################################################
UMIDADE DO SOLO NA TEMP MAIOR
############################################################################################*/

tempMaior=0;

for (i=0; i< 50; i++) {
    dataTemp = datasources["Garden-All"][i]["content"]["temperature"];
        
	if ((tempMaior < dataTemp) && (dataTemp != "nan")) {
		tempMaior = dataTemp;
		hygrometer = datasources["Garden-All"][i]["content"]["hygrometer_value"];
    }
}

return hygrometer;