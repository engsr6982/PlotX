import { CustomForm, EventBus, EventPriority, KeyValueDB, ModalFormSelectedButton } from "levilamina";
import { ModalFormCancelReason, Player } from "minecraft";
import { logger } from "plotx";

/**
 * @param {Player} pl
 */
function main(pl) {
    new CustomForm()
        .setTitle("自定义表单")
        .appendLabel("这是一个标签")
        .appendHeader("这是一个标题")
        .appendDivider()
        .appendInput("input", "输入框", "占位符", "默认值", "输入框说明")
        .appendToggle("toggle", "开关", true, "开关说明")
        .appendDropdown("dropdown", "下拉框", ["选项1", "选项2", "选项3"], 0, "下拉框说明")
        .appendSlider(
            "slider",
            "滑块",
            0, // 最小值
            100, // 最大值
            1, // 步长
            50, // 默认值
            "滑块说明"
        )
        .appendStepSlider(
            "stepSlider",
            "步进滑块",
            ["选项1", "选项2", "选项3"],
            0, // 默认值
            "步进滑块说明"
        )
        .sendTo(pl, (player, result, cancelReason) => {
            logger.debug("Form callback triggered");
            if (result === null) {
                player.sendMessage("表单已取消");
                return;
            }
            player.sendMessage("表单已提交");
            logger.debug(result ? JSON.stringify(result, null, 2) : "表单已取消");
        });
}

const id = EventBus.emplaceListener("PlayerJoinEvent", (ev) => {
    logger.trace("PlayerJoinEvent triggered, id: ", ev.getId());
    let player = ev.self();
    logger.trace("Player: ", player.realName);
    main(player);
    EventBus.removeListener(id);
});

logger.info("Script loaded!");

logger.warn("Enum Bind test: ");
logger.warn("EventPriority: ", JSON.stringify(EventPriority));
logger.warn("ModalFormCancelReason: ", JSON.stringify(ModalFormCancelReason));
logger.warn("ModalFormSelectedButton: ", JSON.stringify(ModalFormSelectedButton));

const db = new KeyValueDB("D:/Codes/PlotCraft-Dev/bin/PlotCraft/data/PlotStorage");

// lambda no this
db.iter((k, v) => {
    logger.warn(`key: ${k}`);
});

// lambda with this
db.iter(function (k, v) {
    logger.warn(`key: ${k}, has: ${this.has(k)}`);
});

try {
    // close
    db.close();
    db.set("test", "testaaaaa"); // error
} catch (e) {
    logger.error(e, "\n", e.stack);
}
