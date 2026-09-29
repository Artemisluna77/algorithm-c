## 工作守则

01 **语言**：必须用中文回复我。
02 **适用范围**：以目标／验收标准／明确约束为最高优先级；不绕过安全、权限、审批与破坏性操作确认；区分事实／推断／假设。
03 **Subagent**：适合并行探索／独立验证／专项审查时可自主调用，不必每次请示；不为用而用；主 agent 负责整合与核验。
04 **第一性**：不套模板，先拆真正目标、输入、约束、事实与假设、最小可行解，再给方案。
05 **根因**：不只修表面，回答为什么发生、现有设计为何允许、根因级方案是什么。
06 **挑战**：不默认用户判断正确，把方案当假设审查，列隐含假设与更优替代。
07 **先懂再改**：改前找文件与调用链、解释现有逻辑、找最小改动点，再动手 + 验证。
08 **自主探索**：给目标就允许自读代码／查上下文／跑测试；路径与目标冲突时以目标为准。
09 **交付闸门**：面向用户的页面／PPT／文档，只留最终内容，清掉作者视角与内部过程。
10 **记忆**：需要历史背景／长期偏好／旧决策时，先检索外置记忆再下结论。
11 **提交闸门**：开发完成后不要主动提交代码（不执行 `git commit`／`git push`）；等我验收，验收通过后由我手动提交。

## 分支规范

格式：`<分支类型>/<日期>-<开发内容>`，例如 `feat/20260913-员工列表分页`。

### 命名规则

- **分支类型**：与本仓库提交信息规范的 type 一致，只能用 `feat`、`fix`、`docs`、`style`、`refactor`、`perf`、`test`、`build`、`ci`、`chore`、`revert`。日常开发最常用 `feat`、`fix`、`chore`、`docs`。
- **日期**：分支创建当天的日期，格式 `YYYYMMDD`，如 `20260913`。
- **开发内容**：简短概括本次开发（建议不超过 15 字），与提交主题同语言、以中文为主，可含必要英文技术词（如 `token`、`echarts`）；多词之间用 `-` 连接。
- **禁止字符**：不含空格，不含 Git 不允许的 `~ ^ : ? * [` `\\`、连续 `..`，不以 `/` 结尾、不以 `.lock` 结尾。

### 使用约束

- **一分支一主题**：一个分支只做一个完整逻辑交付；主题跑偏或范围明显扩大时，另起新分支。
- **从最新基线切出**：先 `git switch main && git pull` 拉到最新，再切出新分支。
- **及时收敛**：开发完成并经用户验收后，合并回 `main`，随后删除本地与远程功能分支，不长期滞留；提交与合并由用户手动执行，agent 不主动提交（见守则 11）。
- **与提交信息联动**：分支内的提交 type/scope 与分支类型保持一致，提交信息遵循 `.trae/rules/git-commit-message.md`。

本仓库当前尚无首个提交；远端 `main` 建立并同步后，再按上述流程从最新基线切出分支。

## Agent skills

### Issue tracker

Issues and specs are tracked as local Markdown files under `.scratch/<feature-slug>/`. See `docs/agents/issue-tracker.md`.

### Triage labels

Use the default labels: `needs-triage`, `needs-info`, `ready-for-agent`, `ready-for-human`, and `wontfix`. See `docs/agents/triage-labels.md`.

### Domain docs

Use the single-context layout: `CONTEXT.md` and `docs/adr/`. See `docs/agents/domain.md`.
