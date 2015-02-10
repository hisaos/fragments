(function(arguments){
  var stepSumToAccept = Number(arguments[0]);
  
  var acceptedStepCodes = [];

  var numShortage = 0;
  var numOver = 0;
  var numDoubleStep = 0;

  var minimumStepNum = findMinimumStepNumber(stepSumToAccept);
  var maximumStepNum = stepSumToAccept;

//  minimumStepCode = findMinimumStepCode(minimumStepNum);
//  maximumStepCode = Math.pow(3, maximumStepNum + 1);

  for(var stepNum = minimumStepNum; stepNum < maximumStepNum; stepNum++)
  {
    minimumStepCode = findMinimumStepCode(stepNum);
    maximumStepCode = findMaximumStepCode(stepNum);
    for(var stepCode = minimumStepCode; stepCode < maximumStepCode + 1; stepCode++)
    {
      stepSumExamined = stepSum(stepCode, stepSumToAccept, stepNum);

      if(stepSumExamined === 0) 
      {
        acceptedStepCodes.push(stepCode);
        print(stepCode);
        printAcceptedStepPattern(stepCode);
      }
      else if(stepSumExamined === "o")
      { // over step
        numOver++;
      }
      else if(stepSumExamined === "s")
      { // shortage
        numShortage++;
      }
    }
  }

  print("# of " + stepSumToAccept + " step pattern:" + acceptedStepCodes.length);
  print("# of over step:" + numOver);
  print("# of shortage:" + numShortage);
})(arguments);

function findMinimumStepCode(stepNum) {
  return Math.pow(3, stepNum);
}

function findMaximumStepCode(stepNum) {
  var code = 0;

  for(var i = 0; i < stepNum; i++) {
    code += Math.pow(3, i) * 2;
  }

  code += Math.pow(3, stepNum);
  return code;
}

function findMinimumStepNumber(numSteps) {
  if(numSteps % 3 === 0) return Math.floor(numSteps / 3);
  else return Math.floor(numSteps / 3) + 1;
}

function stepSum(code, stepSumToAccept, stepNum) {
  var stepToGo = stepSumToAccept + 2;
  var remainStepNum = stepNum;
  var tempCode = code;

  while(tempCode > 0) {
    if(stepToGo < remainStepNum + 2) return "o";
    if(remainStepNum * 3 + 2 < stepToGo) return "s";
    stepToGo -= (tempCode % 3 + 1);
    remainStepNum--;

    tempCode = Math.floor(tempCode / 3);
  }

  return stepToGo;
}

function printAcceptedStepPattern(code) {
  var tempCode = code;
  var stepPattern = []

  while(tempCode > 0) {
    var step = tempCode % 3 + 1;
    stepPattern.push(step);
    tempCode = Math.floor(tempCode / 3);
  }

  print(stepPattern);
}
