import createModule from "./electra.js";

let Electra = null;
let input = null;
let code = null;
let last_output = '';

onmessage = async (e) => {
  let {type, data} = e.data;

  if(type === "start") {
    code = data.code;
    input = data.input;

    if(!Electra) {
      Electra = await createModule();
    }

    loop();
  }
};

function loop() {
  Electra.init(input);
  Electra.set_source_code(code);
  const start = performance.now();
  Electra.generate();
  Electra.step();

  while(Electra.has_currents()) {
    Electra.step();
    const output = Electra.get_output();

    if(output !== last_output) {
      last_output = output;
      postMessage({ type: "output", data: output });
    }
  }
  const end = performance.now();
  const delta_time = (end - start);
  const ms = Math.floor(delta_time % 1000);
  const seconds = Math.floor(delta_time / 1e3) % 60;
  const mins = Math.floor(delta_time / (1e3 * 60)) % 60;
  const hours = Math.floor(delta_time / (1e3 * 3600));
  let final_text = "";
  if(hours > 0) { final_text += `${hours}h `; }
  if(mins > 0) { final_text += `${mins}m `; }
  if(seconds > 0) { final_text += `${seconds}s `; }
  final_text += `${ms}ms`;

  postMessage({ type: "final", data: `\n[Execution completed in ${final_text}]\n` });
}
