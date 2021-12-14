const advent = require('./build/Release/advent');

module.exports = {
    ...advent,
};

/*
const fs = require("fs");

function getProblemData(path) {

    const filePrefix = "file:";
    if(!path.startsWith(filePrefix)) {
        return Promise.resolve(path.split("\n").map(line => line.trim()).filter(n => n !== ""));
    }

    return new Promise((resolve, reject) => {
        fs.readFile(`./data/${path.substring(filePrefix.length)}`, (err, buf) => {
            if(err) {
                return reject(err);
            }
            const lines = buf.toString().split('\n');
            return resolve(lines);
        });
    });
}

const problems = [{
    name: "Depth",
    description: "",
    testData: [
        "file:day1.txt", `
            199,
            200,
            208,
            210,
            200,
            207,
            240,
            269,
            260,
            263,
        `,
    ],
    parser: (line) => parseInt(line),
    solutions: [
        advent.getDepth,
        advent.getDepthByWindow,
    ]
}, {
    name: "Position",
    description: "",
    testData: [
        `
            forward 5
            down 5
            forward 8
            up 3
            down 8
            forward 2
        `,
        "file:day2.txt",
    ],
    parser: (line) => {
        const [command, value] = line.split(' ');
        return {
            command,
            value,
        };
    },
    solutions: [
        advent.getPositionProduct,
        advent.getPositionWithAim,
    ]
}, {
    name: "Bitmask Thing",
    description: "",
    testData: [
        `
            00100
            11110
            10110
            10111
            10101
            01111
            00111
            11100
            10000
            11001
            00010
            01010
        `,
        // "file:day3.txt",
    ],
    parser: (line) => {
        return parseInt(line, 2);
        // return line;
    },
    solutions: [
        advent.getBitAverageThing,
    ],
}, {
    name: "Bingo",
    description: "",
    testData: [
        `
        `,
    ],
    parser: (line) => {
        return line;
    },

}];


function runProblem(problem) {
    Promise.all(problem.testData.map(preParseData => {
        return getProblemData(preParseData).then(data => {
            return data.map(problem.parser);
        })
    })).then(testCases => {
        console.log(`Running ${problem.name}:`);
        problem.solutions.forEach((solution, solutionIndex) => {
            if(!solution) {
                console.log("Solution undefined! Check exports name.");``
                return;
            }

            console.log(`  Solution ${solutionIndex+1} (${solution.name}):`);
            testCases.forEach((testCase, index) => {
                const answer = solution(testCase);
                if(typeof answer === "undefined") {
                    throw new Error("shit hit the fan");
                }

                console.log(`    Test case ${index+1}: ${answer}`);
            });
        });

    });
}

runProblem(problems[2]);
*/