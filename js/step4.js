(function(arguments){
  var stepSumToAccept = Number(arguments[0]);
  
  var acceptedStepCodes = [];

  var numShortage = 0;
  var numOver = 0;
  var numDoubleStep = 0;

  var minimumStepNum = findMinimumStepNumber(stepSumToAccept);
  var maximumStepNum = stepSumToAccept;

  for(var stepNum = minimumStepNum; stepNum < maximumStepNum + 1; stepNum++) {
    print(stepNum);
    minimumStepCode = findMinimumStepCode(stepNum);
    maximumStepCode = findMaximumStepCode(stepNum);

    for(var stepCode = minimumStepCode; stepCode < maximumStepCode + 1; stepCode++) {
      stepSumExamined = stepSum(stepCode, stepSumToAccept, stepNum);

//      if(stepSumExamined === stepSumToAccept) {
      if(stepSumExamined === 0) {
        acceptedStepCodes.push(stepCode);
        print(stepCode);
        printAcceptedStepPattern(stepCode);
      }
      else if(stepSumExamined === "d") { // Double stepped
        numDoubleStep++;
      }
      else if(stepSumExamined === "o") { // over step
        numOver++;
      }
      else if(stepSumExamined === "s") { // shortage
        numShortage++;
      }
    }
  }

//  for(var j = 0; j < acceptedStepCodes.length; j++) {
//    print(acceptedStepCodes[j]);
//    printAcceptedStepPattern(acceptedStepCodes[j]);
//  }

  print("# of " + stepSumToAccept + " step pattern:" + acceptedStepCodes.length);
  print("# of double stepping:" + numDoubleStep);
  print("# of over step:" + numOver);
  print("# of shortage:" + numShortage);
})(arguments);

function findMinimumStepCode(stepNum) {
  var code = 0;

  for(var i = 0; i < stepNum; i++) {
    code += Math.pow(4, i);
  }

  return code;
}

function findMaximumStepCode(stepNum) {
  var code = 0;

  for(var i = 0; i < stepNum; i++) {
    code += Math.pow(4, i) * 3;
  }

  return code;
}

function findMinimumStepNumber(numSteps) {
  if(numSteps % 3 === 0) return Math.floor(numSteps / 3);
  else return Math.floor(numSteps / 3) + 1;
}

function stepSum(code, stepSumToAccept, stepNum) {
  var stepToGo = stepSumToAccept;
  var remainStepNum = stepNum;
  var tempCode = code;

  while(tempCode > 0) {
    if(tempCode % 4 === 0) return "d";
    if(stepToGo < 0) return "o";
    stepToGo -= tempCode % 4;
    remainStepNum--;
    if(remainStepNum * 3 < stepToGo) return "s";

    tempCode = Math.floor(tempCode / 4);
  }

  return stepToGo;
}

function printAcceptedStepPattern(code) {
  var tempCode = code;
  var stepPattern = []

  while(tempCode > 0) {
    if(tempCode % 4 === 0) return -1;
    var step = tempCode % 4;
    stepPattern.push(step);
    tempCode = Math.floor(tempCode / 4);
  }

  print(stepPattern);
}
